#include <stdio.h>
#include <stdlib.h>

#include "misc_includes.hpp"


//#include "gen_src/GrammarLexer.h"
//#include "gen_src/GrammarParser.h"
//static constexpr int some_eof = EOF;
//#include "interpreter_class.hpp"
#include "compiler_class.hpp"


int main(int argc, char** argv)
{
	std::string from_stdin(get_stdin_as_str());

	antlr4::ANTLRInputStream input(from_stdin);
	GrammarLexer lexer(&input);
	antlr4::CommonTokenStream tokens(&lexer);
	tokens.fill();

	GrammarParser parser(&tokens);
	parser.removeErrorListeners();
	std::unique_ptr<CstmErrorListener> cstm_error_listener
		(new CstmErrorListener());
	parser.addErrorListener(cstm_error_listener.get());

	Compiler visitor;
	visitor.visitProgram(parser.program());



	return 0;
}
