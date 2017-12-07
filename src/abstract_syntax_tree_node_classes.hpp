#ifndef abstract_syntax_tree_node_classes_hpp
#define abstract_syntax_tree_node_classes_hpp

#include "misc_includes.hpp"


class AstNodeBase
{
public:		// variables
	

	// Circular linked list links
	AstNodeBase * next, * prev;
};



#endif		// abstract_syntax_tree_node_classes_hpp
