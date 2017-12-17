#include "assembler_class.hpp"


int main(int argc, char** argv)
{
	std::string from_stdin(get_stdin_from_file());;

	antlr4::ANTLRInputStream input(from_stdin);
	GrammarLexer lexer(&input);
	//printout("\n", lexer.getNumberOfSyntaxErrors(), "\n");
	antlr4::CommonTokenStream tokens(&lexer);
	tokens.fill();

	GrammarParser parser(&tokens);
	//printout("\n", parser.getNumberOfSyntaxErrors(), "\n");
	//if (parser.getNumberOfSyntaxErrors())
	//{
	//	exit(1);
	//}
	parser.removeErrorListeners();
	std::unique_ptr<AsmErrorListener> asm_error_listener
		(new AsmErrorListener());
	parser.addErrorListener(asm_error_listener.get());

	Assembler visitor(parser, true);
	return visitor.run();
}
