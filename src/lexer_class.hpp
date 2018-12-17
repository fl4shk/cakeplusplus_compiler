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
		//MiscAuto,
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

private:		// variables
	

public:		// functions
	// Run the lexer
	Token operator () ();

};

} // end namespace cake_plus_plus

#endif		// src_lexer_class_hpp
