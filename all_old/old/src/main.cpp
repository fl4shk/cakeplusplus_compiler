#include "misc_includes.hpp"
#include "abstract_syntax_tree_class.hpp"
//#include "semantic_analyzer_class.hpp"
//#include "ir_code_generator_class.hpp"
//#include "code_generator_class.hpp"
#include "interpreter_class.hpp"

#include "../gen_src/grammar.tab.hh"



int main(int argc, char** argv)
{
	if (yyparse())
	{
		return 1;
	}
	ast.print_json();



	//interpreter.interpret();

	return 0;
}
