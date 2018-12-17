#ifndef src_lexer_class_hpp
#define src_lexer_class_hpp

// src/lexer_class.hpp

#include "source_file_chunk_class.hpp"

namespace cake_plus_plus
{
enum class TokType
{
	InvalidNone,
	InvalidBadHexNum,
	InvalidBadBinNum,

	// End of tokens
	End,

	MiscIdent,
	MiscIntNum,
	//MiscFloatNum,

	MiscStr,

	MiscAuto,
	MiscFunc,

	// Punctuation
	PunctLineComment,

	PunctLParen,
	PunctRParen,
	PunctLBracket,
	PunctRBracket,
	PunctLBrace,
	PunctRBrace,

	PunctSemicolon,
	PunctComma,
	PunctPeriod,


	// Built-in Types
	BuiltinTypeU8,
	BuiltinTypeS8,
	BuiltinTypeU16,
	BuiltinTypeS16,
	BuiltinTypeU32,
	BuiltinTypeS32,
	BuiltinTypeU64,
	BuiltinTypeS64,

	//BuiltinTypeFloat32,
	//BuiltinTypeFloat64,




	// Arithmetic
	OpPlus,
	OpMinus,
	OpMul,
	OpDiv,
	OpModulo,


	// Logical Unops
	OpLogNot,

	// Logical Binops
	OpLogAnd,
	OpLogOr,


	// Bitwise Unops
	OpBitNot,

	// Bitwise Binops
	OpBitAnd,
	OpBitOr,
	OpBitXor,
	OpBitLsl,
	OpBitLsr,
	OpBitAsr,


	// Comparisons
	CmpEq,
	CmpNe,
	CmpLt,
	CmpGe,
	CmpLe,
	CmpGt,

	// Assignments
	AssignRegular,
	AssignPlus,
	AssignMinus,
	AssignMul,
	AssignDiv,
	AssignModulo,

	AssignBitAnd,
	AssignBitOr,
	AssignBitXor,
	AssignBitLsl,
	AssignBitLsr,
	AssignBitAsr,
};

class Lexer;

class Token
{
	friend class Lexer;

private:		// variables
	TokType _type = TokType::InvalidNone;

	ConstStrPtr _str = nullptr;
	u64 _num = 0;


	SourceFileChunk _chunk;
	SourceFilePos2d _pos_2d;

public:		// functions
	inline Token()
	{
	}
	inline Token(const SourceFileChunk& s_chunk)
	{
		_init(s_chunk);
	}

	inline Token(const Token& to_copy) = default;

	virtual inline ~Token()
	{
	}


	inline Token& operator = (const Token& to_copy) = default;

	GEN_GETTER_BY_VAL(type)
	GEN_GETTER_BY_VAL(str)
	GEN_GETTER_BY_VAL(num)
	GEN_GETTER_BY_CON_REF(chunk)
	GEN_GETTER_BY_CON_REF(pos_2d)

protected:		// functions
	inline void _init(const SourceFileChunk& s_chunk)
	{
		_chunk = s_chunk;
		_chunk.get_pos_2d(_pos_2d);
	}

	inline auto _curr_char() const
	{
		return _chunk.curr_char();
	}
	inline bool _has_curr_char() const
	{
		return _chunk.has_curr_char();
	}

	inline auto _next_char()
	{
		const auto ret = _chunk.next_char();
		_pos_2d.next(ret);
		return ret;
	}

	void _eat_whitespace();

	GEN_SETTER_BY_VAL(type)
	GEN_SETTER_BY_VAL(str)
	GEN_SETTER_BY_VAL(num)
	GEN_GETTER_BY_REF(chunk)
	GEN_GETTER_BY_REF(pos_2d)

};

class Lexer
{
protected:		// variables
	Token* _tok = nullptr;


public:		// functions
	// Run the lexer, returning an output token (passed in by reference)
	void operator () (Token& tok, SourceFileChunk& input_chunk);

protected:		// functions
	inline auto curr_char()
	{
		return _tok->_curr_char();
	}
	inline auto has_curr_char()
	{
		return _tok->_has_curr_char();
	}
	inline auto next_char()
	{
		return _tok->_next_char();
	}
	
	GEN_SETTER_BY_VAL(tok)

};

} // end namespace cake_plus_plus

#endif		// src_lexer_class_hpp
