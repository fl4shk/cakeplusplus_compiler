#ifndef assembler_class_hpp
#define assembler_class_hpp

#include "misc_includes.hpp"
#include "ANTLRErrorListener.h"
#include "gen_src/GrammarLexer.h"
#include "gen_src/GrammarParser.h"
#include "gen_src/GrammarVisitor.h"

#include "symbol_table_classes.hpp"


enum class VmInstrOp : u16
{
	constant,
	constant_u32,
	constant_s32,
	constant_u16,
	constant_s16,
	constant_u8,
	constant_s8,

	arg,
	argx,
	var,
	varx,
	get_pc,
	jump,

	beq,
	bne,
	beq_near,
	bne_near,

	call,
	ret,

	ld_basic,
	ld_u32,
	ld_s32,
	ld_u16,
	ld_s16,
	ld_u8,
	ld_s8,

	ldx_basic,
	ldx_u32,
	ldx_s32,
	ldx_u16,
	ldx_s16,
	ldx_u8,
	ldx_s8,

	st_basic,
	st_u32,
	st_s32,
	st_u16,
	st_s16,
	st_u8,
	st_s8,

	stx_basic,
	stx_u32,
	stx_s32,
	stx_u16,
	stx_s16,
	stx_u8,
	stx_s8,

	add_to_sp,

	add,
	sub,
	mul,
	sdiv,
	udiv,
	smod,
	umod,

	bit_and,
	bit_or,
	bit_xor,
	bit_lsl,
	bit_lsr,
	bit_asr,


	cmp_eq,
	cmp_ne,
	cmp_ult,
	cmp_slt,
	cmp_ugt,
	cmp_sgt,
	cmp_ule,
	cmp_sle,
	cmp_uge,
	cmp_sge,


	disp_num,
	disp_num_unsigned,
	disp_char,
	disp_str,
	get_num,

	quit,
};

class AsmErrorListener : public antlr4::ANTLRErrorListener
{
public:		// functions
	virtual ~AsmErrorListener();

	void syntaxError(antlr4::Recognizer *recognizer, 
		antlr4::Token *offendingSymbol, size_t line, 
		size_t charPositionInLine, const std::string &msg, 
		std::exception_ptr e);
	void reportAmbiguity(antlr4::Parser *recognizer, 
		const antlr4::dfa::DFA &dfa, size_t startIndex, size_t stopIndex, 
		bool exact, const antlrcpp::BitSet &ambigAlts, 
		antlr4::atn::ATNConfigSet *configs);
	
	void reportAttemptingFullContext(antlr4::Parser *recognizer, 
		const antlr4::dfa::DFA &dfa, size_t startIndex, size_t stopIndex,
		const antlrcpp::BitSet &conflictingAlts, 
		antlr4::atn::ATNConfigSet *configs);

	void reportContextSensitivity(antlr4::Parser *recognizer, 
		const antlr4::dfa::DFA &dfa, size_t startIndex, size_t stopIndex,
		size_t prediction, antlr4::atn::ATNConfigSet *configs);
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

	bool __show_ws;

public:		// functions
	Assembler(GrammarParser& parser, bool s_show_ws=false);

	int run();

private:		// functions
	inline void print_ws_if_allowed(const std::string some_ws)
	{
		if (__pass && __show_ws)
		{
			printout(some_ws);
		}
	}
	// Generate data
	void gen_no_ws(u16 data);
	void gen_8(u8 data);
	void gen_16(u16 data);
	inline void gen_16(VmInstrOp data)
	{
		gen_16(static_cast<u16>(data));
	}
	void gen_32(u32 data);
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

	antlrcpp::Any visitInstrConst
		(GrammarParser::InstrConstContext *ctx);
	antlrcpp::Any visitInstrConstU32
		(GrammarParser::InstrConstU32Context *ctx);
	antlrcpp::Any visitInstrConstS32
		(GrammarParser::InstrConstS32Context *ctx);
	antlrcpp::Any visitInstrConstU16
		(GrammarParser::InstrConstU16Context *ctx);
	antlrcpp::Any visitInstrConstS16
		(GrammarParser::InstrConstS16Context *ctx);
	antlrcpp::Any visitInstrConstU8
		(GrammarParser::InstrConstU8Context *ctx);
	antlrcpp::Any visitInstrConstS8
		(GrammarParser::InstrConstS8Context *ctx);

	antlrcpp::Any visitInstrArg
		(GrammarParser::InstrArgContext *ctx);
	antlrcpp::Any visitInstrArgX
		(GrammarParser::InstrArgXContext *ctx);
	antlrcpp::Any visitInstrVar
		(GrammarParser::InstrVarContext *ctx);
	antlrcpp::Any visitInstrVarX
		(GrammarParser::InstrVarXContext *ctx);
	antlrcpp::Any visitInstrGetPc
		(GrammarParser::InstrGetPcContext *ctx);
	antlrcpp::Any visitInstrJump
		(GrammarParser::InstrJumpContext *ctx);

	antlrcpp::Any visitInstrBeq
		(GrammarParser::InstrBeqContext *ctx);
	antlrcpp::Any visitInstrBne
		(GrammarParser::InstrBneContext *ctx);
	antlrcpp::Any visitInstrBeqNear
		(GrammarParser::InstrBeqNearContext *ctx);
	antlrcpp::Any visitInstrBneNear
		(GrammarParser::InstrBneNearContext *ctx);

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
	gen_getter_by_ref(sym_tbl);

};



#endif		// assembler_class_hpp
