#include "assembler_class.hpp"
#include "allocation_stuff.hpp"

#include <sstream>

AsmErrorListener::~AsmErrorListener()
{
}

void AsmErrorListener::syntaxError(antlr4::Recognizer *recognizer, 
	antlr4::Token *offendingSymbol, size_t line, 
	size_t charPositionInLine, const std::string &msg, 
	std::exception_ptr e)
{
	printerr("Syntax error on line ", line, 
		", position ", charPositionInLine, 
		":  ", msg, "\n");
	exit(1);
}
void AsmErrorListener::reportAmbiguity(antlr4::Parser *recognizer, 
	const antlr4::dfa::DFA &dfa, size_t startIndex, size_t stopIndex, 
	bool exact, const antlrcpp::BitSet &ambigAlts, 
	antlr4::atn::ATNConfigSet *configs)
{
}

void AsmErrorListener::reportAttemptingFullContext
	(antlr4::Parser *recognizer, const antlr4::dfa::DFA &dfa, 
	size_t startIndex, size_t stopIndex,
	const antlrcpp::BitSet &conflictingAlts, 
	antlr4::atn::ATNConfigSet *configs)
{
}

void AsmErrorListener::reportContextSensitivity
	(antlr4::Parser *recognizer, const antlr4::dfa::DFA &dfa, 
	size_t startIndex, size_t stopIndex, size_t prediction, 
	antlr4::atn::ATNConfigSet *configs)
{
}
Assembler::Assembler(GrammarParser& parser, bool s_show_ws)
	: __show_ws(s_show_ws)
{
	__program_ctx = parser.program();
}

int Assembler::run()
{
	push_scope_child_num(0);
	// Two passes
	for (__pass=0; __pass<2; ++__pass)
	{
		__pc = 0;

		__curr_scope_node = sym_tbl().tree().children.front();

		visitProgram(__program_ctx);

	};

	return 0;
}

void Assembler::gen_no_ws(u16 data)
{
	if (__pass)
	{
		// Output big endian
		printout(std::hex);
		//printout(get_bits_with_range(data, 15, 8), "");
		//printout(get_bits_with_range(data, 7, 0), "\n");
		const u32 a = get_bits_with_range(data, 15, 8);
		const u32 b = get_bits_with_range(data, 7, 0);

		if (a < 0x10)
		{
			printout(0);
		}
		printout(a);

		if (b < 0x10)
		{
			printout(0);
		}
		printout(b);

		printout(std::dec);
	}
	__pc += sizeof(data);
}
void Assembler::gen_8(u8 data)
{
	if (__pass)
	{
		printout(std::hex);

		const u32 a = data;

		if (a < 0x10)
		{
			printout(0);
		}
		printout(a);
		printout(std::dec);
	}
	__pc += sizeof(data);

	print_ws_if_allowed("\n");
}
void Assembler::gen_16(u16 data)
{
	gen_no_ws(data);

	print_ws_if_allowed("\n");
}
void Assembler::gen_32(u32 data)
{
	gen_no_ws(get_bits_with_range(data, 31, 16));
	print_ws_if_allowed(" ");
	gen_no_ws(get_bits_with_range(data, 15, 0));

	print_ws_if_allowed("\n");
}
void Assembler::gen_64(u64 data)
{
	gen_no_ws(get_bits_with_range(data, 63, 48));
	print_ws_if_allowed(" ");
	gen_no_ws(get_bits_with_range(data, 47, 32));
	print_ws_if_allowed(" ");
	gen_no_ws(get_bits_with_range(data, 31, 16));
	print_ws_if_allowed(" ");
	gen_no_ws(get_bits_with_range(data, 15, 0));

	print_ws_if_allowed("\n");
}

antlrcpp::Any Assembler::visitProgram
	(GrammarParser::ProgramContext *ctx)
{
	auto&& lines = ctx->line();

	for (auto line : lines)
	{
		line->accept(this);
	}

	return nullptr;
}

antlrcpp::Any Assembler::visitLine
	(GrammarParser::LineContext *ctx)
{
	if (ctx->scopedLines())
	{
		ctx->scopedLines()->accept(this);
	}
	else if (ctx->label())
	{
		ctx->label()->accept(this);
	}
	else if (ctx->instruction())
	{
		ctx->instruction()->accept(this);
	}
	else if (ctx->comment())
	{
		ctx->comment()->accept(this);
	}
	else if (ctx->directive())
	{
		ctx->directive()->accept(this);
	}
	else
	{
		// blank line
	}

	return nullptr;
}
antlrcpp::Any Assembler::visitScopedLines
	(GrammarParser::ScopedLinesContext *ctx)
{
	if (!__pass)
	{
		sym_tbl().mkscope(__curr_scope_node);
	}
	else // if (__pass)
	{
		__curr_scope_node = __curr_scope_node->children.at
			(get_top_scope_child_num());
		push_scope_child_num(0);
	}
	auto&& lines = ctx->line();

	for (auto line : lines)
	{
		line->accept(this);
	}

	if (!__pass)
	{
		sym_tbl().rmscope(__curr_scope_node);
	}
	else // if (__pass)
	{
		pop_scope_child_num();

		if (__scope_child_num_stack.size() >= 1)
		{
			auto temp = pop_scope_child_num();
			++temp;
			push_scope_child_num(temp);
		}
		__curr_scope_node = __curr_scope_node->parent;
	}

	return nullptr;
}

antlrcpp::Any Assembler::visitLabel
	(GrammarParser::LabelContext *ctx)
{
	ctx->identName()->accept(this);


	auto name = pop_str();

	{
	auto sym = sym_tbl().find_in_this_blklev(__curr_scope_node, name);
	if ((sym != nullptr) && !__pass && sym->found_as_label())
	{
		printerr("Error:  Cannot have two identical identifers!  ",
			"The offending identifier is \"", *name, "\"\n");
		exit(1);
	}
	}
	auto sym = sym_tbl().find_or_insert(__curr_scope_node, name);

	sym->set_found_as_label(true);
	sym->set_addr(pc());

	//printout("visitLabel():  ", pc(), "\n");

	return nullptr;
}


antlrcpp::Any Assembler::visitInstruction
	(GrammarParser::InstructionContext *ctx)
{
	if (ctx->instrConst())
	{
		ctx->instrConst()->accept(this);
	}
	else if (ctx->instrConstU32())
	{
		ctx->instrConstU32()->accept(this);
	}
	else if (ctx->instrConstS32())
	{
		ctx->instrConstS32()->accept(this);
	}
	else if (ctx->instrConstU16())
	{
		ctx->instrConstU16()->accept(this);
	}
	else if (ctx->instrConstS16())
	{
		ctx->instrConstS16()->accept(this);
	}
	else if (ctx->instrConstU8())
	{
		ctx->instrConstU8()->accept(this);
	}
	else if (ctx->instrConstS8())
	{
		ctx->instrConstS8()->accept(this);
	}
	else if (ctx->instrNoImmArgs())
	{
		ctx->instrNoImmArgs()->accept(this);
	}
	else if (ctx->instrBeq())
	{
		ctx->instrBeq()->accept(this);
	}
	else if (ctx->instrBne())
	{
		ctx->instrBne()->accept(this);
	}
	else if (ctx->instrBeqNear())
	{
		ctx->instrBeqNear()->accept(this);
	}
	else if (ctx->instrBneNear())
	{
		ctx->instrBneNear()->accept(this);
	}
	else if (ctx->instrBinop())
	{
		ctx->instrBinop()->accept(this);
	}
	else
	{
		printerr("visitInstruction():  Eek!\n");
		exit(1);
	}

	return nullptr;
}
antlrcpp::Any Assembler::visitInstrConst
	(GrammarParser::InstrConstContext *ctx)
{
	ctx->expr()->accept(this);
	gen_16(VmInstrOp::constant);
	gen_64(pop_num());

	return nullptr;
}
antlrcpp::Any Assembler::visitInstrConstU32
	(GrammarParser::InstrConstU32Context *ctx)
{
	ctx->expr()->accept(this);
	gen_16(VmInstrOp::constant_u32);
	gen_32((u32)pop_num());

	return nullptr;
}
antlrcpp::Any Assembler::visitInstrConstS32
	(GrammarParser::InstrConstS32Context *ctx)
{
	ctx->expr()->accept(this);
	gen_16(VmInstrOp::constant_s32);
	gen_32((s32)pop_num());

	return nullptr;
}
antlrcpp::Any Assembler::visitInstrConstU16
	(GrammarParser::InstrConstU16Context *ctx)
{
	ctx->expr()->accept(this);
	gen_16(VmInstrOp::constant_u16);
	gen_16((u16)pop_num());

	return nullptr;
}
antlrcpp::Any Assembler::visitInstrConstS16
	(GrammarParser::InstrConstS16Context *ctx)
{
	ctx->expr()->accept(this);
	gen_16(VmInstrOp::constant_s16);
	gen_16((s16)pop_num());

	return nullptr;
}
antlrcpp::Any Assembler::visitInstrConstU8
	(GrammarParser::InstrConstU8Context *ctx)
{
	ctx->expr()->accept(this);
	gen_16(VmInstrOp::constant_u8);
	gen_8((u8)pop_num());

	return nullptr;
}
antlrcpp::Any Assembler::visitInstrConstS8
	(GrammarParser::InstrConstS8Context *ctx)
{
	ctx->expr()->accept(this);
	gen_16(VmInstrOp::constant_s8);
	gen_8((s8)pop_num());

	return nullptr;
}

antlrcpp::Any Assembler::visitInstrBeq
	(GrammarParser::InstrBeqContext *ctx)
{
	gen_16(VmInstrOp::beq);

	if (ctx->expr())
	{
		ctx->expr()->accept(this);

		//// subtract 2 because of the gen_16(VmInstrOp::bne)
		//gen_64(pop_num() - pc() - 2);

		//gen_64(pc() - pop_num() - sizeof(u16) - sizeof(s64));
		//gen_64(pc() - pop_num());
		//gen_64(pc() - pop_num() + sizeof(u64));
		gen_64(pop_num() - pc() - sizeof(s64));
	}
	else
	{
		printerr("visitInstrBeq():  Eek!\n");
		exit(1);
	}

	return nullptr;
}
antlrcpp::Any Assembler::visitInstrBne
	(GrammarParser::InstrBneContext *ctx)
{
	gen_16(VmInstrOp::bne);

	if (ctx->expr())
	{
		ctx->expr()->accept(this);

		//// subtract 2 because of the gen_16(VmInstrOp::bne)
		//gen_64(pop_num() - pc() - 2);

		//gen_64(pc() - pop_num() - sizeof(u16) - sizeof(s64));
		//gen_64(pc() - pop_num());
		//gen_64(pc() - pop_num() + sizeof(u64));
		gen_64(pop_num() - pc() - sizeof(s64));
	}
	else
	{
		printerr("visitInstrBne():  Eek!\n");
		exit(1);
	}

	return nullptr;
}
antlrcpp::Any Assembler::visitInstrBeqNear
	(GrammarParser::InstrBeqNearContext *ctx)
{
	gen_16(VmInstrOp::beq_near);

	if (ctx->expr())
	{
		ctx->expr()->accept(this);
		//// subtract 2 because of the gen_16(VmInstrOp::beq)
		//const s64 offset = pop_num() - pc() - 2;

		//const s64 offset = pop_num() - pc() - sizeof(u16) - sizeof(s16);
		//const s64 offset = pc() - pop_num() - sizeof(u16) - sizeof(s16);
		//const s64 offset = pc() - pop_num();
		//const s64 offset = pc() - pop_num() + sizeof(s16);
		const s64 offset = pop_num() - pc() - sizeof(s16);

		//printerr("beq_near(", offset, ")\n");

		if (((s64)((s16)offset)) != offset)
		{
			printerr("beq_near:  Warning:  branch offset of ",
				offset, " out of range for 16-bit signed integer!\n");
		}
		gen_16((s64)((s16)offset));
	}
	else
	{
		printerr("visitInstrBeqNear():  Eek!\n");
		exit(1);
	}
	return nullptr;
}
antlrcpp::Any Assembler::visitInstrBneNear
	(GrammarParser::InstrBneNearContext *ctx)
{
	gen_16(VmInstrOp::bne_near);

	if (ctx->expr())
	{
		ctx->expr()->accept(this);
		//// subtract 2 because of the gen_16(VmInstrOp::bne)
		//const s64 offset = pop_num() - pc() - 2;

		//const s64 offset = pop_num() - pc() - sizeof(u16) - sizeof(s16);
		//const s64 offset = pc() - pop_num() - sizeof(u16) - sizeof(s16);
		//const s64 offset = pc() - pop_num();
		//const s64 offset = pc() - pop_num() + sizeof(s16);
		const s64 offset = -pc() + pop_num() - sizeof(s16);
		//printerr("bne_near(", offset, ")\n");

		if (((s64)((s16)offset)) != offset)
		{
			printerr("bne_near:  Warning:  branch offset of ",
				offset, " out of range for 16-bit signed integer!\n");
		}
		gen_16((s64)((s16)offset));
	}
	else
	{
		printerr("visitInstrBneNear():  Eek!\n");
		exit(1);
	}
	return nullptr;
}
antlrcpp::Any Assembler::visitInstrNoImmArgs
	(GrammarParser::InstrNoImmArgsContext *ctx)
{
	std::string&& op = ctx->TokNoImmArgsOp()->toString();

	if (op == "arg")
	{
		gen_16(VmInstrOp::arg);
	}
	else if (op == "argx")
	{
		gen_16(VmInstrOp::argx);
	}
	else if (op == "var")
	{
		gen_16(VmInstrOp::var);
	}
	else if (op == "varx")
	{
		gen_16(VmInstrOp::varx);
	}
	else if (op == "get_pc")
	{
		gen_16(VmInstrOp::get_pc);
	}
	else if (op == "jump")
	{
		gen_16(VmInstrOp::jump);
	}
	else if (op == "call")
	{
		gen_16(VmInstrOp::call);
	}
	else if (op == "ret")
	{
		gen_16(VmInstrOp::ret);
	}
	else if (__visitInstrLd(op) || __visitInstrLdx(op)
		|| __visitInstrSt(op) || __visitInstrStx(op))
	{
	}
	else if (op == "add_to_sp")
	{
		gen_16(VmInstrOp::add_to_sp);
	}
	else if (op == "disp_num")
	{
		gen_16(VmInstrOp::constant);
		gen_64(VmSyscallShorthandOp::disp_num);
		gen_16(VmInstrOp::syscall);
	}
	else if (op == "disp_num_unsigned")
	{
		gen_16(VmInstrOp::constant);
		gen_64(VmSyscallShorthandOp::disp_num_unsigned);
		gen_16(VmInstrOp::syscall);
	}
	else if (op == "disp_char")
	{
		gen_16(VmInstrOp::constant);
		gen_64(VmSyscallShorthandOp::disp_char);
		gen_16(VmInstrOp::syscall);
	}
	else if (op == "disp_str")
	{
		gen_16(VmInstrOp::constant);
		gen_64(VmSyscallShorthandOp::disp_str);
		gen_16(VmInstrOp::syscall);
	}
	else if (op == "get_num")
	{
		gen_16(VmInstrOp::constant);
		gen_64(VmSyscallShorthandOp::get_num);
		gen_16(VmInstrOp::syscall);
	}
	else if (op == "syscall")
	{
		gen_16(VmInstrOp::syscall);
	}
	else if (op == "quit")
	{
		gen_16(VmInstrOp::quit);
	}
	else
	{
		printerr("visitInstrNoImmArgs():  Eek!\n");
		exit(1);
	}

	return nullptr;
}
bool Assembler::__visitInstrLd(const std::string& op)
{
	if (op == "ld_basic")
	{
		gen_16(VmInstrOp::ld_basic);
	}
	else if (op == "ld_u32")
	{
		gen_16(VmInstrOp::ld_u32);
	}
	else if (op == "ld_s32")
	{
		gen_16(VmInstrOp::ld_s32);
	}
	else if (op == "ld_u16")
	{
		gen_16(VmInstrOp::ld_u16);
	}
	else if (op == "ld_s16")
	{
		gen_16(VmInstrOp::ld_s16);
	}
	else if (op == "ld_u8")
	{
		gen_16(VmInstrOp::ld_u8);
	}
	else if (op == "ld_s8")
	{
		gen_16(VmInstrOp::ld_s8);
	}
	else
	{
		//printerr("__visitInstrLd():  Eek!\n");
		//exit(1);
		return false;
	}

	//return nullptr;
	return true;
}
bool Assembler::__visitInstrLdx(const std::string& op)
{
	if (op == "ldx_basic")
	{
		gen_16(VmInstrOp::ldx_basic);
	}
	else if (op == "ldx_u32")
	{
		gen_16(VmInstrOp::ldx_u32);
	}
	else if (op == "ldx_s32")
	{
		gen_16(VmInstrOp::ldx_s32);
	}
	else if (op == "ldx_u16")
	{
		gen_16(VmInstrOp::ldx_u16);
	}
	else if (op == "ldx_s16")
	{
		gen_16(VmInstrOp::ldx_s16);
	}
	else if (op == "ldx_u8")
	{
		gen_16(VmInstrOp::ldx_u8);
	}
	else if (op == "ldx_s8")
	{
		gen_16(VmInstrOp::ldx_s8);
	}
	else
	{
		//printerr("__visitInstrLdx():  Eek!\n");
		//exit(1);
		return false;
	}

	//return nullptr;
	return true;
}
bool Assembler::__visitInstrSt(const std::string& op)
{
	if (op == "st_basic")
	{
		gen_16(VmInstrOp::st_basic);
	}
	else if (op == "st_u32")
	{
		gen_16(VmInstrOp::st_u32);
	}
	else if (op == "st_s32")
	{
		gen_16(VmInstrOp::st_s32);
	}
	else if (op == "st_u16")
	{
		gen_16(VmInstrOp::st_u16);
	}
	else if (op == "st_s16")
	{
		gen_16(VmInstrOp::st_s16);
	}
	else if (op == "st_u8")
	{
		gen_16(VmInstrOp::st_u8);
	}
	else if (op == "st_s8")
	{
		gen_16(VmInstrOp::st_s8);
	}
	else
	{
		//printerr("__visitInstrSt():  Eek!\n");
		//exit(1);
		return false;
	}

	//return nullptr;
	return true;
}
bool Assembler::__visitInstrStx(const std::string& op)
{
	if (op == "stx_basic")
	{
		gen_16(VmInstrOp::stx_basic);
	}
	else if (op == "stx_u32")
	{
		gen_16(VmInstrOp::stx_u32);
	}
	else if (op == "stx_s32")
	{
		gen_16(VmInstrOp::stx_s32);
	}
	else if (op == "stx_u16")
	{
		gen_16(VmInstrOp::stx_u16);
	}
	else if (op == "stx_s16")
	{
		gen_16(VmInstrOp::stx_s16);
	}
	else if (op == "stx_u8")
	{
		gen_16(VmInstrOp::stx_u8);
	}
	else if (op == "stx_s8")
	{
		gen_16(VmInstrOp::stx_s8);
	}
	else
	{
		//printerr("__visitInstrStx():  Eek!\n");
		//exit(1);
		return false;
	}

	//return nullptr;
	return true;
}
antlrcpp::Any Assembler::visitInstrBinop
	(GrammarParser::InstrBinopContext *ctx)
{
	const auto& some_binop = ctx->TokBinOp()->toString();
	//const auto& some_binop = ctx->getStart()->toString();

	if (some_binop == "add")
	{
		gen_16(VmInstrOp::add);
	}
	else if (some_binop == "sub")
	{
		gen_16(VmInstrOp::sub);
	}
	else if (some_binop == "mul")
	{
		gen_16(VmInstrOp::mul);
	}
	else if (some_binop == "udiv")
	{
		gen_16(VmInstrOp::udiv);
	}
	else if (some_binop == "sdiv")
	{
		gen_16(VmInstrOp::sdiv);
	}
	else if (some_binop == "umod")
	{
		gen_16(VmInstrOp::umod);
	}
	else if (some_binop == "smod")
	{
		gen_16(VmInstrOp::smod);
	}
	else if (some_binop == "bit_and")
	{
		gen_16(VmInstrOp::bit_and);
	}
	else if (some_binop == "bit_or")
	{
		gen_16(VmInstrOp::bit_or);
	}
	else if (some_binop == "bit_xor")
	{
		gen_16(VmInstrOp::bit_xor);
	}
	else if (some_binop == "bit_lsl")
	{
		gen_16(VmInstrOp::bit_lsl);
	}
	else if (some_binop == "bit_lsr")
	{
		gen_16(VmInstrOp::bit_lsr);
	}
	else if (some_binop == "bit_asr")
	{
		gen_16(VmInstrOp::bit_asr);
	}
	else if (some_binop == "cmp_eq")
	{
		gen_16(VmInstrOp::cmp_eq);
	}
	else if (some_binop == "cmp_ne")
	{
		gen_16(VmInstrOp::cmp_ne);
	}
	else if (some_binop == "cmp_ult")
	{
		gen_16(VmInstrOp::cmp_ult);
	}
	else if (some_binop == "cmp_slt")
	{
		gen_16(VmInstrOp::cmp_slt);
	}
	else if (some_binop == "cmp_ugt")
	{
		gen_16(VmInstrOp::cmp_ugt);
	}
	else if (some_binop == "cmp_sgt")
	{
		gen_16(VmInstrOp::cmp_sgt);
	}
	else if (some_binop == "cmp_ule")
	{
		gen_16(VmInstrOp::cmp_ule);
	}
	else if (some_binop == "cmp_sle")
	{
		gen_16(VmInstrOp::cmp_sle);
	}
	else if (some_binop == "cmp_uge")
	{
		gen_16(VmInstrOp::cmp_uge);
	}
	else if (some_binop == "cmp_sge")
	{
		gen_16(VmInstrOp::cmp_sge);
	}
	else
	{
		printerr("visitInstrBinop():  Eek!\n");
		exit(1);
	}
	return nullptr;
}

antlrcpp::Any Assembler::visitComment
	(GrammarParser::CommentContext *ctx)
{
	// Do nothing of interest here
	return nullptr;
}
antlrcpp::Any Assembler::visitDirective
	(GrammarParser::DirectiveContext *ctx)
{
	if (ctx->dotSpaceDirective())
	{
		ctx->dotSpaceDirective()->accept(this);
	}
	else if (ctx->dotDbDirective())
	{
		ctx->dotDbDirective()->accept(this);
	}
	else if (ctx->dotDbU32Directive())
	{
		ctx->dotDbU32Directive()->accept(this);
	}
	else if (ctx->dotDbS32Directive())
	{
		ctx->dotDbS32Directive()->accept(this);
	}
	else if (ctx->dotDbU16Directive())
	{
		ctx->dotDbU16Directive()->accept(this);
	}
	else if (ctx->dotDbS16Directive())
	{
		ctx->dotDbS16Directive()->accept(this);
	}
	else if (ctx->dotDbU8Directive())
	{
		ctx->dotDbU8Directive()->accept(this);
	}
	else if (ctx->dotDbS8Directive())
	{
		ctx->dotDbS8Directive()->accept(this);
	}
	else if (ctx->dotCalliDirective())
	{
		ctx->dotCalliDirective()->accept(this);
	}
	else if (ctx->dotSyscalliDirective())
	{
		ctx->dotSyscalliDirective()->accept(this);
	}
	else
	{
		printerr("visitDirective():  Eek!\n");
		exit(1);
	}

	return nullptr;
}

antlrcpp::Any Assembler::visitDotSpaceDirective
	(GrammarParser::DotSpaceDirectiveContext *ctx)
{
	ctx->expr()->accept(this);

	const auto val = pop_num();

	for (s64 i=0; i<val; ++i)
	{
		gen_8(0);
	}

	return nullptr;
}

antlrcpp::Any Assembler::visitDotDbDirective
	(GrammarParser::DotDbDirectiveContext *ctx)
{
	auto&& expr = ctx->expr();

	for (auto e : expr)
	{
		e->accept(this);
		gen_64(pop_num());
	}

	return nullptr;
}
antlrcpp::Any Assembler::visitDotDbU32Directive
	(GrammarParser::DotDbU32DirectiveContext *ctx)
{
	auto&& expr = ctx->expr();

	for (auto e : expr)
	{
		e->accept(this);
		gen_32((u32)pop_num());
	}

	return nullptr;
}
antlrcpp::Any Assembler::visitDotDbS32Directive
	(GrammarParser::DotDbS32DirectiveContext *ctx)
{
	auto&& expr = ctx->expr();

	for (auto e : expr)
	{
		e->accept(this);
		gen_32((s32)pop_num());
	}

	return nullptr;
}
antlrcpp::Any Assembler::visitDotDbU16Directive
	(GrammarParser::DotDbU16DirectiveContext *ctx)
{
	auto&& expr = ctx->expr();

	for (auto e : expr)
	{
		e->accept(this);
		gen_16((u16)pop_num());
	}

	return nullptr;
}
antlrcpp::Any Assembler::visitDotDbS16Directive
	(GrammarParser::DotDbS16DirectiveContext *ctx)
{
	auto&& expr = ctx->expr();

	for (auto e : expr)
	{
		e->accept(this);
		gen_16((s16)pop_num());
	}

	return nullptr;
}
antlrcpp::Any Assembler::visitDotDbU8Directive
	(GrammarParser::DotDbU8DirectiveContext *ctx)
{
	auto&& expr = ctx->expr();

	for (auto e : expr)
	{
		e->accept(this);
		gen_8((u8)pop_num());
	}

	return nullptr;
}
antlrcpp::Any Assembler::visitDotDbS8Directive
	(GrammarParser::DotDbS8DirectiveContext *ctx)
{
	auto&& expr = ctx->expr();

	for (auto e : expr)
	{
		e->accept(this);
		gen_8((s8)pop_num());
	}

	return nullptr;
}

antlrcpp::Any Assembler::visitDotCalliDirective
	(GrammarParser::DotCalliDirectiveContext *ctx)
{
	ctx->expr()->accept(this);

	gen_16(VmInstrOp::constant);
	gen_64(pop_num());
	gen_16(VmInstrOp::call);

	return nullptr;
}
antlrcpp::Any Assembler::visitDotSyscalliDirective
	(GrammarParser::DotSyscalliDirectiveContext *ctx)
{
	ctx->expr()->accept(this);

	gen_16(VmInstrOp::constant);
	gen_64(pop_num());
	gen_16(VmInstrOp::syscall);

	return nullptr;
}

antlrcpp::Any Assembler::visitExpr
	(GrammarParser::ExprContext *ctx)
{
	if (ctx->expr())
	{
		ctx->expr()->accept(this);
		const auto left = pop_num();

		ctx->exprLogical()->accept(this);
		const auto right = pop_num();

		auto&& op = ctx->TokOpLogical()->toString();

		if (op == "&&")
		{
			push_num(left && right);
		}
		else if (op == "||")
		{
			push_num(left || right);
		}
		else
		{
			printerr("visitExpr():  Eek!\n");
			exit(1);
		}
	}
	else
	{
		ctx->exprLogical()->accept(this);
	}
	return nullptr;
}
antlrcpp::Any Assembler::visitExprLogical
	(GrammarParser::ExprLogicalContext *ctx)
{
	if (ctx->exprLogical())
	{
		ctx->exprLogical()->accept(this);
		const auto left = pop_num();

		ctx->exprCompare()->accept(this);
		const auto right = pop_num();

		auto&& op = ctx->TokOpCompare()->toString();

		if (op == "==")
		{
			push_num(left == right);
		}
		else if (op == "!=")
		{
			push_num(left != right);
		}
		else if (op == "<")
		{
			push_num(left < right);
		}
		else if (op == ">")
		{
			push_num(left > right);
		}
		else if (op == "<=")
		{
			push_num(left <= right);
		}
		else if (op == ">=")
		{
			push_num(left >= right);
		}
		else
		{
			printerr("visitExprLogical():  Eek!\n");
			exit(1);
		}
	}
	else
	{
		ctx->exprCompare()->accept(this);
	}
	return nullptr;
}
antlrcpp::Any Assembler::visitExprCompare
	(GrammarParser::ExprCompareContext *ctx)
{
	if (ctx->exprCompare())
	{
		ctx->exprCompare()->accept(this);
		const auto left = pop_num();

		ctx->exprAddSub()->accept(this);
		const auto right = pop_num();

		auto&& op = ctx->TokOpAddSub()->toString();

		if (op == "+")
		{
			push_num(left + right);
		}
		else if (op == "-")
		{
			push_num(left - right);
		}
		else
		{
			printerr("visitExprCompare():  Eek!\n");
			exit(1);
		}
	}
	else
	{
		ctx->exprAddSub()->accept(this);
	}
	return nullptr;
}
antlrcpp::Any Assembler::visitExprAddSub
	(GrammarParser::ExprAddSubContext *ctx)
{
	if (ctx->exprAddSub())
	{
		ctx->exprAddSub()->accept(this);
		const auto left = pop_num();

		ctx->exprMulDivModEtc()->accept(this);
		const auto right = pop_num();

		//auto&& op = ctx->TokOpAddSub()->toString();
		std::string op;

		if (ctx->TokOpMulDivMod())
		{
			op = ctx->TokOpMulDivMod()->toString();
		}
		else if (ctx->TokOpBitwise())
		{
			op = ctx->TokOpBitwise()->toString();
		}
		else
		{
			printerr("visitExprAddSub():  no op thing eek!\n");
			exit(1);
		}

		if (op == "*")
		{
			push_num(left * right);
		}
		else if (op == "/")
		{
			push_num(left / right);
		}
		else if (op == "%")
		{
			push_num(left % right);
		}
		else if (op == "<<")
		{
			push_num(left << right);
		}
		else if (op == ">>")
		{
			// Logical shift right is special
			const u64 left_u = left;
			const u64 right_u = right;
			const u64 to_push = left_u >> right_u;
			push_num(to_push);
		}
		else if (op == ">>>")
		{
			// This relies upon C++ compilers **usually** performing
			// arithmetic right shifting one signed integer by another
			// 
			// Those C++ compilers that don't support this are not
			// supported for building this assembler!
			push_num(left >> right);
		}
		else
		{
			printerr("visitExprAddSub():  Eek!\n");
			exit(1);
		}
	}
	else
	{
		ctx->exprMulDivModEtc()->accept(this);
	}
	return nullptr;
}
antlrcpp::Any Assembler::visitExprMulDivModEtc
	(GrammarParser::ExprMulDivModEtcContext *ctx)
{
	if (ctx->exprUnary())
	{
		ctx->exprUnary()->accept(this);
	}
	else if (ctx->numExpr())
	{
		ctx->numExpr()->accept(this);
	}
	else if (ctx->identName())
	{
		ctx->identName()->accept(this);

		if (!__pass)
		{
			pop_str();
			push_num(0);
		}
		else
		{
			auto sym = sym_tbl().find_or_insert(__curr_scope_node, 
				pop_str());
			push_num(sym->addr());
		}
	}
	else if (ctx->currPc())
	{
		ctx->currPc()->accept(this);
	}
	else
	{
		ctx->expr()->accept(this);
	}

	return nullptr;
}
antlrcpp::Any Assembler::visitExprUnary
	(GrammarParser::ExprUnaryContext *ctx)
{
	if (ctx->exprBitInvert())
	{
		ctx->exprBitInvert()->accept(this);
	}
	else if (ctx->exprNegate())
	{
		ctx->exprNegate()->accept(this);
	}
	else if (ctx->exprLogNot())
	{
		ctx->exprLogNot()->accept(this);
	}
	else
	{
		printerr("visitExprUnary():  Eek!\n");
		exit(1);
	}
	return nullptr;
}

antlrcpp::Any Assembler::visitExprBitInvert
	(GrammarParser::ExprBitInvertContext *ctx)
{
	ctx->expr()->accept(this);
	push_num(~pop_num());
	return nullptr;
}
antlrcpp::Any Assembler::visitExprNegate
	(GrammarParser::ExprNegateContext *ctx)
{
	ctx->expr()->accept(this);
	push_num(-pop_num());
	return nullptr;
}
antlrcpp::Any Assembler::visitExprLogNot
	(GrammarParser::ExprLogNotContext *ctx)
{
	ctx->expr()->accept(this);
	push_num(!pop_num());
	return nullptr;
}
antlrcpp::Any Assembler::visitIdentName
	(GrammarParser::IdentNameContext *ctx)
{
	if (ctx->TokIdent())
	{
		push_str(cstm_strdup(ctx->TokIdent()->toString()));
	}
	//if (ctx->TokKeywordIdent())
	//{
	//	push_str(cstm_strdup(ctx->TokKeywordIdent()->toString()));
	//}
	else if (ctx->TokBinOp())
	{
		push_str(cstm_strdup(ctx->TokBinOp()->toString()));
	}
	else if (ctx->TokNoImmArgsOp())
	{
		push_str(cstm_strdup(ctx->TokNoImmArgsOp()->toString()));
	}
	else
	{
		printerr("visitIdentName():  Eek!\n");
		exit(1);
	}

	return nullptr;
}
antlrcpp::Any Assembler::visitNumExpr
	(GrammarParser::NumExprContext *ctx)
{
	s64 to_push;


	std::stringstream sstm;
	if (ctx->TokDecNum())
	{
		sstm << ctx->TokDecNum()->toString();
		sstm >> to_push;
	}
	else if (ctx->TokChar())
	{
		std::string temp;
		sstm << ctx->TokChar()->toString();
		sstm >> temp;

		to_push = temp.at(1);
	}

	push_num(to_push);

	return nullptr;
}
antlrcpp::Any Assembler::visitCurrPc
	(GrammarParser::CurrPcContext *ctx)
{
	push_num(__pc);

	return nullptr;
}
