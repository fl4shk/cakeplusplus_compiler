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

	static inline const std::vector<StrPtr> TUP_TYPES_VEC
	= {
		cstm_strdup("Const"),
		cstm_strdup("Unop"),
		cstm_strdup("Binop"),
		cstm_strdup("LdSt"),
		cstm_strdup("UncondJump"),
		cstm_strdup("CondJump"),
		cstm_strdup("Call"),
		cstm_strdup("Ret"),
		cstm_strdup("Label"),
	};

	static inline const std::vector<StrPtr> UNOPS_VEC
	= {
		// Logical
		cstm_strdup("LogNot"),

		// Bitwise
		cstm_strdup("BitNot"),
	};


	static inline const std::vector<StrPtr> BINOPS_VEC
	= {
		// Arithmetic
		cstm_strdup("Add"),
		cstm_strdup("Sub"),
		cstm_strdup("Mul"),
		cstm_strdup("UDiv"),
		cstm_strdup("SDiv"),
		cstm_strdup("UMod"),
		cstm_strdup("SMod"),

		// Compares
		cstm_strdup("CmpEq"),
		cstm_strdup("CmpNe"),
		cstm_strdup("CmpLtu"),
		cstm_strdup("CmpGeu"),
		cstm_strdup("CmpLeu"),
		cstm_strdup("CmpGtu"),
		cstm_strdup("CmpLts"),
		cstm_strdup("CmpGes"),
		cstm_strdup("CmpLes"),
		cstm_strdup("CmpGts"),

		// Logical
		cstm_strdup("LogAnd"),
		cstm_strdup("LogOr"),

		// Bitwise
		cstm_strdup("BitAnd"),
		cstm_strdup("BitOr"),
		cstm_strdup("BitXor"),
		cstm_strdup("BitLsl"),
		cstm_strdup("BitLsr"),
		cstm_strdup("BitAsr"),
	};

private:		// variables

	StrPtr _tup_type;
	ExprType _expr_type;
	StrPtr _unop;
	StrPtr _binop;
	size_t _num_args;


public:		// functions

};

} // end namespace cake_plus_plus

#endif		// src_tac_tuple_class_hpp
