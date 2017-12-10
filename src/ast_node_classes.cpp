#include "ast_node_classes.hpp"


AstNode::AstNode()
{
}
AstNode::~AstNode()
{
}

void AstNode::append_child(AstNode* some_child)
{
	for (AstNode* iter : children)
	{
		if (iter == some_child)
		{
			printerr("AstNode::append_child():  Eek!\n");
			exit(1);
		}
	}

	children.push_back(some_child);
}


void AstNode::append_to_list(AstNode* to_append)
{
	for (AstNode* iter : list)
	{
		if (iter == to_append)
		{
			printerr("AstNode::append_to_list():  Eek!\n");
		}
	}

	list.push_back(to_append);
}


void AstNode::output_to_json(Json::Value& json_node) const
{
	json_node["_node"] = to_string();

	if (children.size() != 0)
	{
		auto& recursive_node = json_node["for_the_childrens"];

		for (size_t i=0; i<children.size(); ++i)
		{
			const Json::ArrayIndex index_i = i;
			children.at(i)->output_to_json(recursive_node[index_i]);
		}
	}
}

std::ostream& operator << (std::ostream& os, AstNode* to_print)
{
	osprintout(os, "[");

	to_print->osprint(os);

	for (auto* iter : to_print->children)
	{
		osprintout(os, iter);
	}
	osprintout(os, "]");

	return os;
}
