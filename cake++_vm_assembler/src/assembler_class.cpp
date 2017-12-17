#include "assembler_class.hpp"
#include "allocation_stuff.hpp"

#include <sstream>

Assembler::Assembler(GrammarParser& parser, bool s_show_ws)
	: __show_ws(s_show_ws)
{
	__program_ctx = parser.program();
}

int Assembler::run()
{
	// Two passes
	for (__pass=0; __pass<2; ++__pass)
	{
		__pc = 0;

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

	for (auto& line : lines)
	{
		line->accept(this);
	}

	return nullptr;
}

antlrcpp::Any Assembler::visitLine
	(GrammarParser::LineContext *ctx)
{
	if (ctx->label())
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
	else
	{
		// blank line
	}

	return nullptr;
}

antlrcpp::Any Assembler::visitLabel
	(GrammarParser::LabelContext *ctx)
{
	ctx->identName()->accept(this);


	auto name = pop_str();

	auto sym = sym_tbl().find_or_insert(name);

	if (!__pass && sym->found_as_label())
	{
		printerr("Error:  Cannot have two identical identifers!  ",
			"The offending identifier is \"", *name, "\"\n");
		exit(1);
	}

	sym->set_found_as_label(true);
	sym->set_addr(pc());

	return nullptr;
}


antlrcpp::Any Assembler::visitInstruction
	(GrammarParser::InstructionContext *ctx)
{

	//else
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
	gen_16(VmInstrOp::constant_u32);
	gen_32((u32)pop_num());

	return nullptr;
}
antlrcpp::Any Assembler::visitInstrConstU16
	(GrammarParser::InstrConstU16Context *ctx)
{
	ctx->expr()->accept(this);
	gen_16(VmInstrOp::constant_u32);
	gen_16((u16)pop_num());

	return nullptr;
}
antlrcpp::Any Assembler::visitInstrConstS16
	(GrammarParser::InstrConstS16Context *ctx)
{
	ctx->expr()->accept(this);
	gen_16(VmInstrOp::constant_u32);
	gen_16((s16)pop_num());

	return nullptr;
}
antlrcpp::Any Assembler::visitInstrConstU8
	(GrammarParser::InstrConstU8Context *ctx)
{
	ctx->expr()->accept(this);

	return nullptr;
}
antlrcpp::Any Assembler::visitInstrConstS8
	(GrammarParser::InstrConstS8Context *ctx)
{
	ctx->expr()->accept(this);
	gen_16(VmInstrOp::constant_u32);
	gen_16((s16)pop_num());

	return nullptr;
}

antlrcpp::Any Assembler::visitInstrArg
	(GrammarParser::InstrArgContext *ctx)
{
	gen_16(VmInstrOp::arg);
	return nullptr;
}
antlrcpp::Any Assembler::visitInstrArgX
	(GrammarParser::InstrArgXContext *ctx)
{
	gen_16(VmInstrOp::argx);
	return nullptr;
}
antlrcpp::Any Assembler::visitInstrVar
	(GrammarParser::InstrVarContext *ctx)
{
	gen_16(VmInstrOp::var);
	return nullptr;
}
antlrcpp::Any Assembler::visitInstrVarX
	(GrammarParser::InstrVarXContext *ctx)
{
	gen_16(VmInstrOp::varx);
	return nullptr;
}
antlrcpp::Any Assembler::visitInstrGetPc
	(GrammarParser::InstrGetPcContext *ctx)
{
	gen_16(VmInstrOp::get_pc);
	return nullptr;
}
antlrcpp::Any Assembler::visitInstrJump
	(GrammarParser::InstrJumpContext *ctx)
{
	gen_16(VmInstrOp::jump);
	return nullptr;
}
antlrcpp::Any Assembler::visitInstrBeq
	(GrammarParser::InstrBeqContext *ctx)
{
	gen_16(VmInstrOp::beq);

	if (ctx->expr())
	{
		ctx->expr()->accept(this);
		// subtract 2 because of the gen_16(VmInstrOp::bne)
		gen_64(pop_num() - pc() - 2);
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
		// subtract 2 because of the gen_16(VmInstrOp::bne)
		gen_64(pop_num() - pc() - 2);
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
		// subtract 2 because of the gen_16(VmInstrOp::beq)
		const s64 offset = pop_num() - pc() - 2;

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
		// subtract 2 because of the gen_16(VmInstrOp::bne)
		const s64 offset = pop_num() - pc() - 2;

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
antlrcpp::Any Assembler::visitInstrCall
	(GrammarParser::InstrCallContext *ctx)
{
	gen_16(VmInstrOp::call);
	return nullptr;
}
antlrcpp::Any Assembler::visitInstrRet
	(GrammarParser::InstrRetContext *ctx)
{
	gen_16(VmInstrOp::ret);
	return nullptr;
}
antlrcpp::Any Assembler::visitInstrLd
	(GrammarParser::InstrLdContext *ctx)
{
	std::string&& op = ctx->TokLdOp()->toString();

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
		printerr("visitInstrLd():  Eek!\n");
		exit(1);
	}

	return nullptr;
}
antlrcpp::Any Assembler::visitInstrLdx
	(GrammarParser::InstrLdxContext *ctx)
{
	std::string&& op = ctx->TokLdxOp()->toString();

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
		printerr("visitInstrLdx():  Eek!\n");
		exit(1);
	}

	return nullptr;
}
antlrcpp::Any Assembler::visitInstrSt
	(GrammarParser::InstrStContext *ctx)
{
	std::string&& op = ctx->TokStOp()->toString();

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
		printerr("visitInstrSt():  Eek!\n");
		exit(1);
	}

	return nullptr;
}
antlrcpp::Any Assembler::visitInstrStx
	(GrammarParser::InstrStxContext *ctx)
{
	std::string&& op = ctx->TokStxOp()->toString();

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
		printerr("visitInstrStx():  Eek!\n");
		exit(1);
	}

	return nullptr;
}
antlrcpp::Any Assembler::visitInstrBinop
	(GrammarParser::InstrBinopContext *ctx)
{
	const auto& some_binop = ctx->TokBinOp()->toString();

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
	else if (some_binop == "sdiv")
	{
		gen_16(VmInstrOp::sdiv);
	}
	else if (some_binop == "udiv")
	{
		gen_16(VmInstrOp::udiv);
	}
	else if (some_binop == "smod")
	{
		gen_16(VmInstrOp::smod);
	}
	else if (some_binop == "umod")
	{
		gen_16(VmInstrOp::umod);
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

antlrcpp::Any Assembler::visitInstrDispNum
	(GrammarParser::InstrDispNumContext *ctx)
{
	gen_16(VmInstrOp::disp_num);
	return nullptr;
}
antlrcpp::Any Assembler::visitInstrDispNumUnsigned
	(GrammarParser::InstrDispNumUnsignedContext *ctx)
{
	gen_16(VmInstrOp::disp_num_unsigned);
	return nullptr;
}
antlrcpp::Any Assembler::visitInstrDispChar
	(GrammarParser::InstrDispCharContext *ctx)
{
	gen_16(VmInstrOp::disp_char);
	return nullptr;
}
antlrcpp::Any Assembler::visitInstrDispStr
	(GrammarParser::InstrDispStrContext *ctx)
{
	gen_16(VmInstrOp::disp_str);
	return nullptr;
}
antlrcpp::Any Assembler::visitInstrGetNum
	(GrammarParser::InstrGetNumContext *ctx)
{
	gen_16(VmInstrOp::get_num);
	return nullptr;
}
antlrcpp::Any Assembler::visitInstrQuit
	(GrammarParser::InstrQuitContext *ctx)
{
	gen_16(VmInstrOp::quit);
	return nullptr;
}


antlrcpp::Any Assembler::visitComment
	(GrammarParser::CommentContext *ctx)
{
	// Do nothing of interest here
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
	if (ctx->numExpr())
	{
		ctx->numExpr()->accept(this);
	}
	else if (ctx->identName())
	{
		ctx->identName()->accept(this);
		auto sym = sym_tbl().find_or_insert(pop_str());
		push_num(sym->addr());
	}
	else if (ctx->currPc())
	{
		ctx->currPc()->accept(this);
	}
	else if (ctx->TokOpUnary())
	{
		ctx->expr()->accept(this);
		const auto stuff = pop_num();

		auto&& op = ctx->TokOpUnary()->toString();

		if (op == "~")
		{
			push_num(~stuff);
		}
		else if (op == "-")
		{
			push_num(-stuff);
		}
		else if (op == "!")
		{
			push_num(!stuff);
		}
		else
		{
			printerr("visitExprMulDivModEtc():  Eek!\n");
			exit(1);
		}
	}
	else
	{
		ctx->expr()->accept(this);
	}

	return nullptr;
}

antlrcpp::Any Assembler::visitIdentName
	(GrammarParser::IdentNameContext *ctx)
{
	push_str(cstm_strdup(ctx->TokIdent()->toString()));

	return nullptr;
}
antlrcpp::Any Assembler::visitNumExpr
	(GrammarParser::NumExprContext *ctx)
{
	std::stringstream sstm;

	s64 to_push;
	sstm << ctx->TokDecNum()->toString();
	sstm >> to_push;
	push_num(to_push);

	return nullptr;
}
antlrcpp::Any Assembler::visitCurrPc
	(GrammarParser::CurrPcContext *ctx)
{
	push_num(__pc);

	return nullptr;
}
