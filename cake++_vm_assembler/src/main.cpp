#include "assembler_class.hpp"


int main(int argc, char** argv)
{
	std::string from_stdin(get_stdin_from_file());;

	antlr4::ANTLRInputStream input(from_stdin);
	GrammarLexer lexer(&input);
	antlr4::CommonTokenStream tokens(&lexer);
	tokens.fill();

	GrammarParser parser(&tokens);

	Assembler visitor(parser, true);
	return visitor.run();
}
