#include "misc_includes.hpp"



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
	return 0;
}
