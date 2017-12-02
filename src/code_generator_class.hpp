#ifndef code_generator_class_hpp
#define code_generator_class_hpp

#include "misc_includes.hpp"
#include "../gen_src/grammar.tab.hh"
#include "symbol_table_extern_funcs.hpp"

class Tuple
{
public:		// variables
	
};


class CodeGenerator
{
public:		// classes

private:		// variables
	std::vector<Tuple> __code;

public:		// functions
	int gen_constant(int some_num);
	int gen_load(const std::string& some_var_name);

	// gen_store() implicitly uses assign_ident_str for the destination.
	int gen_store(int index);
	int gen_logical_and(int index_a, int index_b);
	int gen_logical_or(int index_a, int index_b);
	int gen_cmp_eq(int index_a, int index_b);
	int gen_cmp_ne(int index_a, int index_b);
	int gen_cmp_lt(int index_a, int index_b);
	int gen_cmp_gt(int index_a, int index_b);
	int gen_cmp_le(int index_a, int index_b);
	int gen_cmp_ge(int index_a, int index_b);
	int gen_add(int index_a, int index_b);
	int gen_sub(int index_a, int index_b);
	int gen_mul(int index_a, int index_b);
	int gen_div(int index_a, int index_b);
	int gen_mod(int index_a, int index_b);
	int gen_bitwise_and(int index_a, int index_b);
	int gen_bitwise_or(int index_a, int index_b);
	int gen_bitwise_xor(int index_a, int index_b);

};

extern CodeGenerator codegen;

#endif		// code_generator_class_hpp
