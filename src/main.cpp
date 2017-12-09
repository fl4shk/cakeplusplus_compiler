#include "misc_includes.hpp"
//#include "ir_code_generator_class.hpp"
#include "abstract_syntax_tree_class.hpp"

#include "../gen_src/grammar.tab.hh"



int main(int argc, char** argv)
{
	if (yyparse())
	{
		return 1;
	}
	ast.print();

	//codegen.generate();
	return 0;
}
