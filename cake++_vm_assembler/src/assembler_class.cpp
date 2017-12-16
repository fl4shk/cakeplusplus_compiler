#include "assembler_class.hpp"
#include "allocation_stuff.hpp"

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
		// Big endian
		printout(get_bits_with_range(data, 15, 8));
		printout(get_bits_with_range(data, 7, 0));
	}
	__pc += sizeof(data);
}
void Assembler::gen_64(u64 data)
{
	if (__pass)
	{
		// Big endian
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
	return nullptr;
}

antlrcpp::Any Assembler::visitLine
	(GrammarParser::LineContext *ctx)
{
	return nullptr;
}

antlrcpp::Any Assembler::visitLabel
	(GrammarParser::LabelContext *ctx)
{
	return nullptr;
}


antlrcpp::Any Assembler::visitInstruction
	(GrammarParser::InstructionContext *ctx)
{
	return nullptr;
}
antlrcpp::Any Assembler::visitInstrConstant
	(GrammarParser::InstrConstantContext *ctx)
{
	return nullptr;
}
antlrcpp::Any Assembler::visitInstrArg
	(GrammarParser::InstrArgContext *ctx)
{
	return nullptr;
}
antlrcpp::Any Assembler::visitInstrArgX
	(GrammarParser::InstrArgXContext *ctx)
{
	return nullptr;
}
antlrcpp::Any Assembler::visitInstrVar
	(GrammarParser::InstrVarContext *ctx)
{
	return nullptr;
}
antlrcpp::Any Assembler::visitInstrVarX
	(GrammarParser::InstrVarXContext *ctx)
{
	return nullptr;
}
antlrcpp::Any Assembler::visitInstrGetArgSpace
	(GrammarParser::InstrGetArgSpaceContext *ctx)
{
	return nullptr;
}
antlrcpp::Any Assembler::visitInstrSetArgSpace
	(GrammarParser::InstrSetArgSpaceContext *ctx)
{
	return nullptr;
}
antlrcpp::Any Assembler::visitInstrGetPc
	(GrammarParser::InstrGetPcContext *ctx)
{
	return nullptr;
}
antlrcpp::Any Assembler::visitInstrJump
	(GrammarParser::InstrJumpContext *ctx)
{
	return nullptr;
}
antlrcpp::Any Assembler::visitInstrBeq
	(GrammarParser::InstrBeqContext *ctx)
{
	return nullptr;
}
antlrcpp::Any Assembler::visitInstrBne
	(GrammarParser::InstrBneContext *ctx)
{
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
	return nullptr;
}
antlrcpp::Any Assembler::visitNumExpr
	(GrammarParser::NumExprContext *ctx)
{
	return nullptr;
}
antlrcpp::Any Assembler::visitCurrPc
	(GrammarParser::CurrPcContext *ctx)
{
	return nullptr;
}
