#ifndef src_tac_tuple_class_hpp
#define src_tac_tuple_class_hpp

// src/tac_tuple_class.hpp

#include "misc_includes.hpp"
#include "misc_helper_defines.hpp"
#include "expr_type_stuff.hpp"
#include "symbol_table_class.hpp"
#include "alloc_stuff.hpp"

namespace cake_plus_plus
{

// Three-address code tuple
class TacTuple
{
public:		// constants

	static inline const std::vector<ConstStrPtr> TUP_TYPES_VEC
	= {
		ensure_unique("Const"),
		ensure_unique("Unop"),
		ensure_unique("Binop"),
		ensure_unique("LdSt"),
		ensure_unique("UncondJump"),
		ensure_unique("CondJump"),
		ensure_unique("Call"),
		ensure_unique("Ret"),
		ensure_unique("Label"),
	};

	static inline const std::vector<ConstStrPtr> UNOPS_VEC
	= {
		// Logical
		ensure_unique("LogNot"),

		// Bitwise
		ensure_unique("BitNot"),
	};


	static inline const std::vector<ConstStrPtr> BINOPS_VEC
	= {
		// Arithmetic
		ensure_unique("Add"),
		ensure_unique("Sub"),
		ensure_unique("Mul"),
		ensure_unique("UDiv"),
		ensure_unique("SDiv"),
		ensure_unique("UMod"),
		ensure_unique("SMod"),

		// Compares
		ensure_unique("CmpEq"),
		ensure_unique("CmpNe"),
		ensure_unique("CmpLtu"),
		ensure_unique("CmpGeu"),
		ensure_unique("CmpLeu"),
		ensure_unique("CmpGtu"),
		ensure_unique("CmpLts"),
		ensure_unique("CmpGes"),
		ensure_unique("CmpLes"),
		ensure_unique("CmpGts"),

		// Logical
		ensure_unique("LogAnd"),
		ensure_unique("LogOr"),

		// Bitwise
		ensure_unique("BitAnd"),
		ensure_unique("BitOr"),
		ensure_unique("BitXor"),
		ensure_unique("BitLsl"),
		ensure_unique("BitLsr"),
		ensure_unique("BitAsr"),
	};

private:		// variables

	ConstStrPtr _tup_type;
	ExprType _expr_type;
	ConstStrPtr _unop;
	ConstStrPtr _binop;
	size_t _num_args;


public:		// functions

};

} // end namespace cake_plus_plus

#endif		// src_tac_tuple_class_hpp
