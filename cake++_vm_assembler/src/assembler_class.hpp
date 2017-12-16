#ifndef assembler_class_hpp
#define assembler_class_hpp

#include "misc_includes.hpp"
#include "gen_src/GrammarLexer.h"
#include "gen_src/GrammarParser.h"
#include "gen_src/GrammarVisitor.h"

#include "symbol_table_classes.hpp"


enum class VmInstrOp : u16
{
	constant,
	arg,
	argx,
	var,
	varx,
	get_arg_space,
	set_arg_space,
	get_pc,
	jump,
	beq,
	bne,
	call,
	ret,
	ld,
	ldx,
	st,
	stx,

	binop,

	disp_num,
	disp_num_unsigned,
	disp_char,
	disp_str,
	get_num,

	quit,
};

enum class VmInstrLdStOp : u16
{
	Basic,
	U32,
	S32,
	U16,
	S16,
	U8,
	S8
};

enum class VmInstrBinOp : u16
{
	Add,
	Sub,
	Mul,
	SDiv,
	UDiv,
	SMod,
	UMod,

	BitAnd,
	BitOr,
	BitXor,
	BitLsl,
	BitLsr,
	BitAsr,


	CmpEq,
	CmpNe,


	CmpULt,
	CmpSLt,


	CmpUGt,
	CmpSGt,


	CmpULe,
	CmpSLe,


	CmpUGe,
	CmpSGe,
};

class Assembler : public GrammarVisitor
{
private:		// variables
	SymbolTable __sym_tbl;

	u64 __pc;

	std::stack<s64> __num_stack;
	std::stack<std::string*> __str_stack;

	GrammarParser::ProgramContext* __program_ctx;
	int __pass;

public:		// functions
	Assembler(GrammarParser& parser);

	int run();

private:		// functions
	void gen_16(u16 data);
	void gen_64(u64 data);

	/**
	* Visit parse trees produced by GrammarParser.
	*/
	antlrcpp::Any visitProgram
		(GrammarParser::ProgramContext *ctx);

	antlrcpp::Any visitLine
		(GrammarParser::LineContext *ctx);

	antlrcpp::Any visitLabel
		(GrammarParser::LabelContext *ctx);


	antlrcpp::Any visitInstruction
		(GrammarParser::InstructionContext *ctx);
	antlrcpp::Any visitInstrConstant
		(GrammarParser::InstrConstantContext *ctx);
	antlrcpp::Any visitInstrArg
		(GrammarParser::InstrArgContext *ctx);
	antlrcpp::Any visitInstrArgX
		(GrammarParser::InstrArgXContext *ctx);
	antlrcpp::Any visitInstrVar
		(GrammarParser::InstrVarContext *ctx);
	antlrcpp::Any visitInstrVarX
		(GrammarParser::InstrVarXContext *ctx);
	antlrcpp::Any visitInstrGetArgSpace
		(GrammarParser::InstrGetArgSpaceContext *ctx);
	antlrcpp::Any visitInstrSetArgSpace
		(GrammarParser::InstrSetArgSpaceContext *ctx);
	antlrcpp::Any visitInstrGetPc
		(GrammarParser::InstrGetPcContext *ctx);
	antlrcpp::Any visitInstrJump
		(GrammarParser::InstrJumpContext *ctx);
	antlrcpp::Any visitInstrBeq
		(GrammarParser::InstrBeqContext *ctx);
	antlrcpp::Any visitInstrBne
		(GrammarParser::InstrBneContext *ctx);
	antlrcpp::Any visitInstrCall
		(GrammarParser::InstrCallContext *ctx);
	antlrcpp::Any visitInstrRet
		(GrammarParser::InstrRetContext *ctx);
	antlrcpp::Any visitInstrLd
		(GrammarParser::InstrLdContext *ctx);
	antlrcpp::Any visitInstrLdx
		(GrammarParser::InstrLdxContext *ctx);
	antlrcpp::Any visitInstrSt
		(GrammarParser::InstrStContext *ctx);
	antlrcpp::Any visitInstrStx
		(GrammarParser::InstrStxContext *ctx);
	antlrcpp::Any visitInstrBinop
		(GrammarParser::InstrBinopContext *ctx);
	antlrcpp::Any visitInstrDispNum
		(GrammarParser::InstrDispNumContext *ctx);
	antlrcpp::Any visitInstrDispNumUnsigned
		(GrammarParser::InstrDispNumUnsignedContext *ctx);
	antlrcpp::Any visitInstrDispChar
		(GrammarParser::InstrDispCharContext *ctx);
	antlrcpp::Any visitInstrDispStr
		(GrammarParser::InstrDispStrContext *ctx);
	antlrcpp::Any visitInstrGetNum
		(GrammarParser::InstrGetNumContext *ctx);
	antlrcpp::Any visitInstrQuit
		(GrammarParser::InstrQuitContext *ctx);


	antlrcpp::Any visitComment
		(GrammarParser::CommentContext *ctx);

	antlrcpp::Any visitExpr
		(GrammarParser::ExprContext *ctx);
	antlrcpp::Any visitExprLogical
		(GrammarParser::ExprLogicalContext *ctx);
	antlrcpp::Any visitExprCompare
		(GrammarParser::ExprCompareContext *ctx);
	antlrcpp::Any visitExprAddSub
		(GrammarParser::ExprAddSubContext *ctx);
	antlrcpp::Any visitExprMulDivModEtc
		(GrammarParser::ExprMulDivModEtcContext *ctx);

	antlrcpp::Any visitIdentName
		(GrammarParser::IdentNameContext *ctx);
	antlrcpp::Any visitNumExpr
		(GrammarParser::NumExprContext *ctx);
	antlrcpp::Any visitCurrPc
		(GrammarParser::CurrPcContext *ctx);

private:		// functions
	inline void push_num(s64 to_push)
	{
		__num_stack.push(to_push);
	}
	inline auto get_top_num()
	{
		return __num_stack.top();
	}
	inline auto pop_num()
	{
		auto ret = __num_stack.top();
		__num_stack.pop();
		return ret;
	}

	inline void push_str(std::string* to_push)
	{
		__str_stack.push(to_push);
	}
	inline auto get_top_str()
	{
		return __str_stack.top();
	}
	inline auto pop_str()
	{
		auto ret = __str_stack.top();
		__str_stack.pop();
		return ret;
	}

	gen_getter_and_setter_by_val(pc);

};



#endif		// assembler_class_hpp
