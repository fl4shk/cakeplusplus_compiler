#include "misc_includes.hpp"
#include "ir_code_generator_class.hpp"



int main(int argc, char** argv)
{
	//yylex();
	////for (s64 i=0; i<3; ++i)
	////{
	////	printout("i == ", i, "\n");
	////}

	//printout("Here is my funky amount of identifiers:  ", ident_count, 
	//	"\n");
	//printout("Here is my funky amount of dec_numbers:  ", dec_num_count, 
	//	"\n");
	yyparse();
	ircodegen.print();
	return 0;
}
