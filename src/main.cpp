#include <stdio.h>
#include <stdlib.h>

#include "misc_includes.hpp"


//#include "gen_src/GrammarLexer.h"
//#include "gen_src/GrammarParser.h"
//static constexpr int some_eof = EOF;
#include "interpreter_class.hpp"


int main(int argc, char** argv)
{
	std::string from_stdin(get_stdin_from_file());;

	antlr4::ANTLRInputStream input(from_stdin);
	GrammarLexer lexer(&input);
	antlr4::CommonTokenStream tokens(&lexer);
	tokens.fill();

	GrammarParser parser(&tokens);
	//antlr4::tree::ParseTree* tree = parser.program();
	auto program = parser.program();

	//printout(tree->toStringTree(&parser), "\n", "\n");
	Interpreter visitor;
	visitor.visitProgram(program);



	return 0;
}
