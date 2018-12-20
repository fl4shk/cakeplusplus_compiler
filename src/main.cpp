#include "compiler_class.hpp"
#include "compiler_error_listener_class.hpp"

int main(int argc, char** argv)
{
	std::string from_stdin(get_stdin_as_str());

	antlr4::ANTLRInputStream input(from_stdin);
	CompilerGrammarLexer lexer(&input);
	antlr4::CommonTokenStream tokens(&lexer);
	tokens.fill();

	CompilerGrammarParser parser(&tokens);
	parser.removeErrorListeners();
	std::unique_ptr<cake_plus_plus::CompilerErrorListener>
		compiler_error_listener
		(new cake_plus_plus::CompilerErrorListener());
	parser.addErrorListener(compiler_error_listener.get());

	cake_plus_plus::Compiler visitor(parser);
	return visitor.run();
}
