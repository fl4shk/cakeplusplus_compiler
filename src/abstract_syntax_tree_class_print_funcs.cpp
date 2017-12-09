#include "abstract_syntax_tree_class.hpp"

void AbstractSyntaxTree::print_json() const
{
	Json::Value output_root;

	liborangepower::json::write_json(cout, &output_root);
}
