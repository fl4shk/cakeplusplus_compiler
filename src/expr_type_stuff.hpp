#ifndef src_expr_type_stuff_hpp
#define src_expr_type_stuff_hpp

// src/expr_type_stuff.hpp

#include "misc_includes.hpp"

namespace cake_plus_plus
{

enum class ExprType
{
	// Integer Types
	U8,
	S8,
	U16,
	S16,
	U32,
	S32,
	U64,
	S64,

	//// Floating Point Types
	//Float32,
	//Float64,

	// Custom types such as classes and typedefs
	Custom,
};

} // end namespace cake_plus_plus

#endif		// src_expr_type_stuff_hpp
