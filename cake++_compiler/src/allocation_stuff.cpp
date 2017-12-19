#include "allocation_stuff.hpp"
#include "symbol_table_classes.hpp"
//#include "abstract_syntax_tree_classes.hpp"


std::map<int, std::unique_ptr<int>> AllocStuff::__int_pool;
std::map<std::string, std::unique_ptr<std::string>> AllocStuff::__str_pool;
std::vector<std::unique_ptr<VmCode>> AllocStuff::__vm_code_pool;
//std::vector<std::unique_ptr<AstNode>> AllocStuff::__ast_node_pool;

int* cstm_intdup(int to_dup)
{
	auto& pool = AllocStuff::__int_pool;

	if (pool.count(to_dup) == 0)
	{
		std::unique_ptr<int> to_insert;
		to_insert.reset(new int());
		*to_insert = to_dup;
		pool[to_dup] = std::move(to_insert);
	}

	return pool.at(to_dup).get();
}

std::string* cstm_strdup(const std::string& to_dup)
{
	auto& pool = AllocStuff::__str_pool;

	if (pool.count(to_dup) == 0)
	{
		std::unique_ptr<std::string> to_insert;
		to_insert.reset(new std::string());
		*to_insert = to_dup;
		pool[to_dup] = std::move(to_insert);
	}

	return pool.at(to_dup).get();
}


//AstNode* mk_ast_node()
//{
//	auto& pool = AllocStuff::__ast_node_pool;
//
//	std::unique_ptr<AstNode> p;
//	p.reset(new AstNode());
//
//	pool.push_back(std::move(p));
//	return pool.back().get();
//}
