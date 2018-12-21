#ifndef src_parser_class_hpp
#define src_parser_class_hpp

// src/parser_class.hpp

#include "lexer_class.hpp"
#include "ast_node_classes.hpp"

namespace cake_plus_plus
{

class Parser
{
protected:		// variables
	Lexer* _lexer;
	AstNodeBase* _ast;
	std::vector<std::unique_ptr<AstNodeBase>> _nodes_of_ast;

public:		// functions
	Parser(Lexer* s_lexer);

	virtual ~Parser();

	void run(const std::string& file_contents);

protected:		// functions
	template<typename NodeType>
	inline AstNodeBase* mk_node()
	{
		_nodes_of_ast.push_back(std::unique_ptr<AstNodeBase>
			(new NodeType()));
		return _nodes_of_ast.back().get();
	}
	bool parse_program(bool just_test);
	bool parse_list_functions(bool just_test);
	bool parse_function(bool just_test);
};

} // end namespace cake_plus_plus


#endif		// src_parser_class_hpp
