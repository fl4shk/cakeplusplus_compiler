#include "allocation_stuff.hpp"
#include "symbol_table_classes.hpp"
//#include "abstract_syntax_tree_classes.hpp"


std::map<int, std::unique_ptr<int>> AllocStuff::__int_pool;
std::map<std::string, std::unique_ptr<std::string>> AllocStuff::__str_pool;
std::vector<std::unique_ptr<VmCode>> AllocStuff::__vm_code_pool;
std::vector<std::unique_ptr<IrCode>> AllocStuff::__ir_code_pool;
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

VmCode* append_vm_code(VmCode& some_head)
{
	auto& pool = AllocStuff::__vm_code_pool;

	std::unique_ptr<VmCode> p;
	p.reset(new VmCode());
	p->next = &some_head;
	(p->prev = some_head.prev)->next = p.get();
	some_head.prev = p.get();

	pool.push_back(std::move(p));
	return pool.back().get();
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


//IrCode* append_ir_code(IrCode& some_head)
//{
//	auto& pool = AllocStuff::__ir_code_pool;
//
//	std::unique_ptr<IrCode> p;
//	p.reset(new IrCode());
//	p->next = &some_head;
//	(p->prev = some_head.prev)->next = p.get();
//	some_head.prev = p.get();
//
//	pool.push_back(std::move(p));
//	return pool.back().get();
//}

IrCode* mk_linked_ir_code(Function& curr_func)
{
	auto p = mk_unlinked_ir_code();

	auto to_link_after = curr_func.ir_code().prev;

	IrCode* old_next = to_link_after->next;

	to_link_after->next = p;
	p->prev = to_link_after;
	p->next = old_next;
	old_next->prev = p;

	return p;
}
IrCode* mk_linked_ir_code(Function& curr_func, IrOp s_op)
{
	auto p = mk_linked_ir_code(curr_func);
	p->op = s_op;
	return p;
}

IrCode* mk_unlinked_ir_code()
{
	auto& pool = AllocStuff::__ir_code_pool;

	std::unique_ptr<IrCode> p;
	p.reset(new IrCode());

	pool.push_back(std::move(p));
	return pool.back().get();
}

IrCode* mk_unlinked_ir_code(IrOp s_op)
{
	auto p = mk_unlinked_ir_code();
	p->op = s_op;
	return p;
}
