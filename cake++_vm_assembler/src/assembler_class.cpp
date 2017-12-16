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

	if (ctx->identName())
	{
		ctx->identName()->accept(this);

		auto sym = sym_tbl().find_or_insert(pop_str());

		// subtract 2 because of the gen_16(VmInstrOp::beq)
		gen_64(sym->addr() - pc() - 2);
	}
	else if (ctx->expr())
	{
		ctx->expr()->accept(this);
		// subtract 2 because of the gen_16(VmInstrOp::beq)
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

	if (ctx->identName())
	{
		ctx->identName()->accept(this);

		auto sym = sym_tbl().find_or_insert(pop_str());
		// subtract 2 because of the gen_16(VmInstrOp::bne)
		gen_64(sym->addr() - pc() - 2);
	}
	else if (ctx->expr())
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
antlrcpp::Any Assembler::visitInstrCall
	(GrammarParser::InstrCallContext *ctx)
{
	return nullptr;
}
antlrcpp::Any Assembler::visitInstrRet
	(GrammarParser::InstrRetContext *ctx)
{
	return nullptr;
}
antlrcpp::Any Assembler::visitInstrLd
	(GrammarParser::InstrLdContext *ctx)
{
	return nullptr;
}
antlrcpp::Any Assembler::visitInstrLdx
	(GrammarParser::InstrLdxContext *ctx)
{
	return nullptr;
}
antlrcpp::Any Assembler::visitInstrSt
	(GrammarParser::InstrStContext *ctx)
{
	return nullptr;
}
antlrcpp::Any Assembler::visitInstrStx
	(GrammarParser::InstrStxContext *ctx)
{
	return nullptr;
}
antlrcpp::Any Assembler::visitInstrBinop
	(GrammarParser::InstrBinopContext *ctx)
{
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
