#ifndef src_tac_tuple_class_hpp
#define src_tac_tuple_class_hpp

// src/tac_tuple_class.hpp

#include "misc_includes.hpp"
#include "misc_helper_defines.hpp"
#include "expr_type_stuff.hpp"
#include "symbol_table_class.hpp"

namespace cake_plus_plus
{

// Three-address code tuple
class TacTuple
{
public:		// constants

	// Nope, I'm not using std::initializer_list.  You can't make me.
	static inline const std::string TUP_TYPES_ARR[]
	= {
		"Const",
		"Unop",
		"Binop",
		"LdSt",
		"UncondJump",
		"CondJump",
		"Call",
		"Ret",
		"Label",
	};
	static inline const size_t NUM_TUP_TYPES
		= CONST_ARR_SIZE(TUP_TYPES_ARR);

	static inline const std::string UNOPS_ARR[]
	= {
		// Logical
		"LogNot",

		// Bitwise
		"BitNot",
	};
	static inline const size_t NUM_UNOPS
		= CONST_ARR_SIZE(UNOPS_ARR);


	static inline const std::string BINOPS_ARR[]
	= {
		// Arithmetic
		"Add",
		"Sub",
		"Mul",
		"UDiv",
		"SDiv",
		"UMod",
		"SMod",

		// Compares
		"CmpEq",
		"CmpNe",
		"CmpLtu",
		"CmpGeu",
		"CmpLeu",
		"CmpGtu",
		"CmpLts",
		"CmpGes",
		"CmpLes",
		"CmpGts",

		// Logical
		"LogAnd",
		"LogOr",

		// Bitwise
		"BitAnd",
		"BitOr",
		"BitXor",
		"BitLsl",
		"BitLsr",
		"BitAsr",
	};

	static inline const size_t NUM_BINOPS
		= CONST_ARR_SIZE(BINOPS_ARR);

private:		// variables

	std::string* _tup_type;
	std::string* _unop;
	std::string* _binop;


public:		// functions

};

} // end namespace cake_plus_plus

#endif		// src_tac_tuple_class_hpp
