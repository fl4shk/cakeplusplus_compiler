#ifndef src_lexer_class_hpp
#define src_lexer_class_hpp

// src/lexer_class.hpp

#include "source_file_chunk_class.hpp"

namespace cake_plus_plus
{
enum class TokType
{
	Bad,
	End,

	MiscIdent,
	MiscNum,

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
	TokType _tok_type = TokType::Bad;
	size_t _line_num = 0, _pos_in_line = 0;

	ConstStrPtr _str = nullptr;
	u64 _num = 0;

	SourceFilePos2d _pos_2d;

	SourceFileChunk _chunk;

public:		// functions
	inline Token()
	{
	}
	inline Token(const SourceFileChunk& s_chunk)
	{
		init(s_chunk);
	}

	inline Token(const Token& to_copy) = default;

	virtual inline ~Token()
	{
	}

	inline void init(const SourceFileChunk& s_chunk)
	{
		_chunk = s_chunk;
		_chunk.get_pos_2d(_pos_2d);
	}

	inline Token& operator = (const Token& to_copy) = default;

	inline auto curr_char() const
	{
		return _chunk.curr_char();
	}
	inline bool has_curr_char() const
	{
		return _chunk.has_curr_char();
	}

	inline auto next_char()
	{
		const auto ret = _chunk.next_char();
		_pos_2d.next(ret);
		return ret;
	}

	void eat_whitespace();

	GEN_GETTER_AND_SETTER_BY_VAL(tok_type)
	GEN_GETTER_AND_SETTER_BY_VAL(str)
	GEN_GETTER_AND_SETTER_BY_VAL(num)

	GEN_GETTER_BY_CON_REF(pos_2d)
	GEN_GETTER_BY_CON_REF(chunk)
};

class Lexer
{
public:		// enums

public:		// classes

private:		// functions


public:		// functions
	// Run the lexer
	Token operator () (const SourceFileChunk& input_chunk) const;

};

} // end namespace cake_plus_plus

#endif		// src_lexer_class_hpp
