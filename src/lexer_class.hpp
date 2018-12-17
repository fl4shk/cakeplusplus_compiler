#ifndef src_lexer_class_hpp
#define src_lexer_class_hpp

// src/lexer_class.hpp

#include "source_file_chunk_class.hpp"

namespace cake_plus_plus
{

class Lexer
{
public:		// enums
	enum class Token
	{
		Bad,
		EndingWhitespace,

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

public:		// classes
	class Result
	{
	private:		// variables
		Token _tok = Token::Bad;
		ConstStrPtr _str = nullptr;
		u64 _num = 0;

		SourceFileChunk _chunk;

	public:		// functions
		inline Result()
		{
		}
		//inline Result(Token s_tok, ConstStrPtr s_str, u64 s_num,
		//	const SourceFileChunk& s_chunk)
		//	: _tok(s_tok), _str(s_str), _num(s_num), _chunk(s_chunk)
		//{
		//}
		inline Result(const SourceFileChunk& s_chunk)
			: _chunk(s_chunk)
		{
		}

		inline Result(const Result& to_copy) = default;

		virtual inline ~Result()
		{
		}

		inline Result& operator = (const Result& to_copy) = default;

		GEN_GETTER_AND_SETTER_BY_VAL(tok)
		GEN_GETTER_AND_SETTER_BY_VAL(str)
		GEN_GETTER_AND_SETTER_BY_VAL(num)
		GEN_GETTER_BY_REF(chunk)
	};

private:		// functions
	void _eat_whitespace(Result& result) const;
	//bool _attempt_handle_keyword(Result& result) const;



public:		// functions
	// Run the lexer
	Result operator () (const SourceFileChunk& input_chunk) const;

};

} // end namespace cake_plus_plus

#endif		// src_lexer_class_hpp
