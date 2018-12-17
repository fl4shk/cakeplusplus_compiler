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
		unique_dup("Const"),
		unique_dup("Unop"),
		unique_dup("Binop"),
		unique_dup("LdSt"),
		unique_dup("UncondJump"),
		unique_dup("CondJump"),
		unique_dup("Call"),
		unique_dup("Ret"),
		unique_dup("Label"),
	};

	static inline const std::vector<ConstStrPtr> UNOPS_VEC
	= {
		// Logical
		unique_dup("LogNot"),

		// Bitwise
		unique_dup("BitNot"),
	};


	static inline const std::vector<ConstStrPtr> BINOPS_VEC
	= {
		// Arithmetic
		unique_dup("Add"),
		unique_dup("Sub"),
		unique_dup("Mul"),
		unique_dup("UDiv"),
		unique_dup("SDiv"),
		unique_dup("UMod"),
		unique_dup("SMod"),

		// Compares
		unique_dup("CmpEq"),
		unique_dup("CmpNe"),
		unique_dup("CmpLtu"),
		unique_dup("CmpGeu"),
		unique_dup("CmpLeu"),
		unique_dup("CmpGtu"),
		unique_dup("CmpLts"),
		unique_dup("CmpGes"),
		unique_dup("CmpLes"),
		unique_dup("CmpGts"),

		// Logical
		unique_dup("LogAnd"),
		unique_dup("LogOr"),

		// Bitwise
		unique_dup("BitAnd"),
		unique_dup("BitOr"),
		unique_dup("BitXor"),
		unique_dup("BitLsl"),
		unique_dup("BitLsr"),
		unique_dup("BitAsr"),
	};

private:		// variables

	ConstStrPtr _tup_type;
	//ExprType _expr_type;
	ConstStrPtr _unop;
	ConstStrPtr _binop;
	size_t _num_args;


public:		// functions

};

} // end namespace cake_plus_plus

#endif		// src_tac_tuple_class_hpp
