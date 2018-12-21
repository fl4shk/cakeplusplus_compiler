#include "parser_class.hpp"

namespace cake_plus_plus
{

Parser::Parser(Lexer* s_lexer)
	: _lexer(s_lexer)
{
	_ast = mk_node<AstNodeProgram>();
}

Parser::~Parser()
{
}

bool Parser::parse_program(bool just_test)
{
	return false;
}
bool Parser::parse_list_functions(bool just_test)
{
	return false;
}
bool Parser::parse_function(bool just_test)
{
	return false;
}

} // end namespace cake_plus_plus
