#include "assembler_class.hpp"
#include "allocation_stuff.hpp"

#include <sstream>

Assembler::Assembler(GrammarParser& parser)
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

void Assembler::gen_16(u16 data)
{
	if (__pass)
	{
		// Output big endian
		printout(get_bits_with_range(data, 15, 8));
		printout(get_bits_with_range(data, 7, 0));
	}
	__pc += sizeof(data);
}
void Assembler::gen_64(u64 data)
{
	if (__pass)
	{
		// Output big endian
		printout(get_bits_with_range(data, 63, 56));
		printout(get_bits_with_range(data, 55, 48));
		printout(get_bits_with_range(data, 47, 40));
		printout(get_bits_with_range(data, 39, 32));
		printout(get_bits_with_range(data, 31, 24));
		printout(get_bits_with_range(data, 23, 16));
		printout(get_bits_with_range(data, 15, 8));
		printout(get_bits_with_range(data, 7, 0));
	}
	__pc += sizeof(data);
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
	return nullptr;
}


antlrcpp::Any Assembler::visitInstruction
	(GrammarParser::InstructionContext *ctx)
{

	if (ctx->instrConstant())
	{
		ctx->instrConstant()->accept(this);
	}
	else if (ctx->instrArg())
	{
		ctx->instrArg()->accept(this);
	}
	else if (ctx->instrArgX())
	{
		ctx->instrArgX()->accept(this);
	}
	else if (ctx->instrVar())
	{
		ctx->instrVar()->accept(this);
	}
	else if (ctx->instrVarX())
	{
		ctx->instrVarX()->accept(this);
	}
	else if (ctx->instrGetArgSpace())
	{
		ctx->instrGetArgSpace()->accept(this);
	}
	else if (ctx->instrSetArgSpace())
	{
		ctx->instrSetArgSpace()->accept(this);
	}
	else if (ctx->instrGetPc())
	{
		ctx->instrGetPc()->accept(this);
	}
	else if (ctx->instrJump())
	{
		ctx->instrJump()->accept(this);
	}
	else if (ctx->instrBeq())
	{
		ctx->instrBeq()->accept(this);
	}
	else if (ctx->instrBne())
	{
		ctx->instrBne()->accept(this);
	}
	else if (ctx->instrCall())
	{
		ctx->instrCall()->accept(this);
	}
	else if (ctx->instrRet())
	{
		ctx->instrRet()->accept(this);
	}
	else if (ctx->instrLd())
	{
		ctx->instrLd()->accept(this);
	}
	else if (ctx->instrLdx())
	{
		ctx->instrLdx()->accept(this);
	}
	else if (ctx->instrSt())
	{
		ctx->instrSt()->accept(this);
	}
	else if (ctx->instrStx())
	{
		ctx->instrStx()->accept(this);
	}
	else if (ctx->instrBinop())
	{
		ctx->instrBinop()->accept(this);
	}
	else if (ctx->instrDispNum())
	{
		ctx->instrDispNum()->accept(this);
	}
	else if (ctx->instrDispNumUnsigned())
	{
		ctx->instrDispNumUnsigned()->accept(this);
	}
	else if (ctx->instrDispChar())
	{
		ctx->instrDispChar()->accept(this);
	}
	else if (ctx->instrDispStr())
	{
		ctx->instrDispStr()->accept(this);
	}
	else if (ctx->instrGetNum())
	{
		ctx->instrGetNum()->accept(this);
	}
	else if (ctx->instrQuit())
	{
		ctx->instrQuit()->accept(this);
	}
	else
	{
		printerr("visitInstruction():  Eek!\n");
		exit(1);
	}

	return nullptr;
}
antlrcpp::Any Assembler::visitInstrConstant
	(GrammarParser::InstrConstantContext *ctx)
{
	ctx->expr()->accept(this);
	gen_16(VmInstrOp::constant);
	gen_64(pop_num());

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
antlrcpp::Any Assembler::visitInstrGetArgSpace
	(GrammarParser::InstrGetArgSpaceContext *ctx)
{
	gen_16(VmInstrOp::get_arg_space);
	return nullptr;
}
antlrcpp::Any Assembler::visitInstrSetArgSpace
	(GrammarParser::InstrSetArgSpaceContext *ctx)
{
	gen_16(VmInstrOp::set_arg_space);
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
	gen_16(VmInstrOp::ld);

	gen_ldst_op(ctx->TokBuiltinTypename()->toString(),
		"visitInstrLd():  Eek!\n");

	return nullptr;
}
antlrcpp::Any Assembler::visitInstrLdx
	(GrammarParser::InstrLdxContext *ctx)
{
	gen_16(VmInstrOp::ldx);

	gen_ldst_op(ctx->TokBuiltinTypename()->toString(),
		"visitInstrLdx():  Eek!\n");

	return nullptr;
}
antlrcpp::Any Assembler::visitInstrSt
	(GrammarParser::InstrStContext *ctx)
{
	gen_16(VmInstrOp::st);

	gen_ldst_op(ctx->TokBuiltinTypename()->toString(),
		"visitInstrSt():  Eek!\n");

	return nullptr;
}
antlrcpp::Any Assembler::visitInstrStx
	(GrammarParser::InstrStxContext *ctx)
{
	gen_16(VmInstrOp::stx);

	gen_ldst_op(ctx->TokBuiltinTypename()->toString(),
		"visitInstrStx():  Eek!\n");

	return nullptr;
}
antlrcpp::Any Assembler::visitInstrBinop
	(GrammarParser::InstrBinopContext *ctx)
{
	gen_16(VmInstrOp::binop);

	const auto& some_binop = ctx->TokBinOp()->toString();

	if (some_binop == "add")
	{
		gen_16(VmInstrBinOp::Add);
	}
	else if (some_binop == "sub")
	{
		gen_16(VmInstrBinOp::Sub);
	}
	else if (some_binop == "mul")
	{
		gen_16(VmInstrBinOp::Mul);
	}
	else if (some_binop == "sdiv")
	{
		gen_16(VmInstrBinOp::SDiv);
	}
	else if (some_binop == "udiv")
	{
		gen_16(VmInstrBinOp::UDiv);
	}
	else if (some_binop == "smod")
	{
		gen_16(VmInstrBinOp::SMod);
	}
	else if (some_binop == "umod")
	{
		gen_16(VmInstrBinOp::UMod);
	}
	else if (some_binop == "bitand")
	{
		gen_16(VmInstrBinOp::BitAnd);
	}
	else if (some_binop == "bitor")
	{
		gen_16(VmInstrBinOp::BitOr);
	}
	else if (some_binop == "bitxor")
	{
		gen_16(VmInstrBinOp::BitXor);
	}
	else if (some_binop == "bitlsl")
	{
		gen_16(VmInstrBinOp::BitLsl);
	}
	else if (some_binop == "bitlsr")
	{
		gen_16(VmInstrBinOp::BitLsr);
	}
	else if (some_binop == "bitasr")
	{
		gen_16(VmInstrBinOp::BitAsr);
	}
	else if (some_binop == "cmpeq")
	{
		gen_16(VmInstrBinOp::CmpEq);
	}
	else if (some_binop == "cmpne")
	{
		gen_16(VmInstrBinOp::CmpNe);
	}
	else if (some_binop == "cmpult")
	{
		gen_16(VmInstrBinOp::CmpULt);
	}
	else if (some_binop == "cmpslt")
	{
		gen_16(VmInstrBinOp::CmpSLt);
	}
	else if (some_binop == "cmpugt")
	{
		gen_16(VmInstrBinOp::CmpUGt);
	}
	else if (some_binop == "cmpsgt")
	{
		gen_16(VmInstrBinOp::CmpSGt);
	}
	else if (some_binop == "cmpule")
	{
		gen_16(VmInstrBinOp::CmpULe);
	}
	else if (some_binop == "cmpsle")
	{
		gen_16(VmInstrBinOp::CmpSLe);
	}
	else if (some_binop == "cmpuge")
	{
		gen_16(VmInstrBinOp::CmpUGe);
	}
	else if (some_binop == "cmpsge")
	{
		gen_16(VmInstrBinOp::CmpSGe);
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
	return nullptr;
}
antlrcpp::Any Assembler::visitInstrDispNumUnsigned
	(GrammarParser::InstrDispNumUnsignedContext *ctx)
{
	return nullptr;
}
antlrcpp::Any Assembler::visitInstrDispChar
	(GrammarParser::InstrDispCharContext *ctx)
{
	return nullptr;
}
antlrcpp::Any Assembler::visitInstrDispStr
	(GrammarParser::InstrDispStrContext *ctx)
{
	return nullptr;
}
antlrcpp::Any Assembler::visitInstrGetNum
	(GrammarParser::InstrGetNumContext *ctx)
{
	return nullptr;
}
antlrcpp::Any Assembler::visitInstrQuit
	(GrammarParser::InstrQuitContext *ctx)
{
	return nullptr;
}


antlrcpp::Any Assembler::visitComment
	(GrammarParser::CommentContext *ctx)
{
	return nullptr;
}

antlrcpp::Any Assembler::visitExpr
	(GrammarParser::ExprContext *ctx)
{
	return nullptr;
}
antlrcpp::Any Assembler::visitExprLogical
	(GrammarParser::ExprLogicalContext *ctx)
{
	return nullptr;
}
antlrcpp::Any Assembler::visitExprCompare
	(GrammarParser::ExprCompareContext *ctx)
{
	return nullptr;
}
antlrcpp::Any Assembler::visitExprAddSub
	(GrammarParser::ExprAddSubContext *ctx)
{
	return nullptr;
}
antlrcpp::Any Assembler::visitExprMulDivModEtc
	(GrammarParser::ExprMulDivModEtcContext *ctx)
{
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


void Assembler::gen_ldst_op(const std::string& some_typename, 
	const std::string& eek_msg)
{
	if (some_typename == "basic")
	{
		gen_16(VmInstrLdStOp::Basic);
	}
	else if (some_typename == "u32")
	{
		gen_16(VmInstrLdStOp::U32);
	}
	else if (some_typename == "s32")
	{
		gen_16(VmInstrLdStOp::S32);
	}
	else if (some_typename == "u16")
	{
		gen_16(VmInstrLdStOp::U16);
	}
	else if (some_typename == "s16")
	{
		gen_16(VmInstrLdStOp::S16);
	}
	else if (some_typename == "u8")
	{
		gen_16(VmInstrLdStOp::U8);
	}
	else if (some_typename == "s8")
	{
		gen_16(VmInstrLdStOp::S8);
	}
	else
	{
		printerr(eek_msg);
		exit(1);
	}
}
