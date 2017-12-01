#include "misc_includes.hpp"

extern "C"
{
u64 count;

int real_main(int argc, char** argv)
{
	yylex();
	//for (s64 i=0; i<3; ++i)
	//{
	//	printout("i == ", i, "\n");
	//}

	printout("Here is my funky amount of identifiers:  ", count, "\n");
	return 0;
}

void inc_count()
{
	printout("Nice\n");
	++count;
}
}
