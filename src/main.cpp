#include "misc_includes.hpp"

extern "C"
{
u64 ident_count, num_count;

int real_main(int argc, char** argv)
{
	yylex();
	//for (s64 i=0; i<3; ++i)
	//{
	//	printout("i == ", i, "\n");
	//}

	printout("Here is my funky amount of identifiers:  ", ident_count, 
		"\n");
	printout("Here is my funky amount of numbers:  ", num_count, 
		"\n");
	return 0;
}

void inc_ident_count()
{
	//printout("Nice\n");
	++ident_count;
}

void inc_num_count()
{
	++num_count;
}

}
