#include "allocation_stuff.hpp"
#include "symbol_table_classes.hpp"
//#include "abstract_syntax_tree_classes.hpp"


std::map<int, std::unique_ptr<int>> AllocStuff::__int_pool;
std::map<std::string, std::unique_ptr<std::string>> AllocStuff::__str_pool;
std::vector<std::unique_ptr<Var>> AllocStuff::__var_pool;

std::vector<std::unique_ptr<BackendCodeBase>>
	AllocStuff::__backend_code_base_pool;
std::vector<std::unique_ptr<IrExpr>> AllocStuff::__ir_expr_pool;
std::vector<std::unique_ptr<IrCode>> AllocStuff::__ir_code_pool;

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

Var* mk_var()
{
	auto& pool = AllocStuff::__var_pool;

	std::unique_ptr<Var> p;
	p.reset(new Var());

	pool.push_back(std::move(p));
	return pool.back().get();
}
Var* mk_var(Ident s_name, BuiltinTypename s_type, size_t s_size, 
	Function* s_func)
{
	auto& pool = AllocStuff::__var_pool;

	std::unique_ptr<Var> p;
	p.reset(new Var(s_name, s_type, s_size, s_func));

	pool.push_back(std::move(p));
	return pool.back().get();
}

IrExpr* mk_ir_pure_expr(IrPureExOp s_pure_op, IrMachineMode s_mm)
{
	return mk_ir_pure_expr(s_pure_op, s_mm, nullptr);
}

IrExpr* mk_ir_pure_expr(IrPureExOp s_pure_op, IrMachineMode s_mm, 
	IrExpr* some_parent)
{
	auto& pool = AllocStuff::__ir_expr_pool;

	std::unique_ptr<IrExpr> p;
	p.reset(new IrExpr(some_parent));
	p->pure_op = s_pure_op;
	p->is_pure = true;
	p->mm = s_mm;

	pool.push_back(std::move(p));
	return pool.back().get();
}

IrExpr* mk_ir_spec_expr(IrSpecExOp s_spec_op, IrMachineMode s_mm)
{
	return mk_ir_spec_expr(s_spec_op, s_mm, nullptr);
}

IrExpr* mk_ir_spec_expr(IrSpecExOp s_spec_op, IrMachineMode s_mm, 
	IrExpr* some_parent)
{
	auto& pool = AllocStuff::__ir_expr_pool;

	std::unique_ptr<IrExpr> p;
	p.reset(new IrExpr(some_parent));
	p->spec_op = s_spec_op;
	p->is_pure = false;
	p->mm = s_mm;

	pool.push_back(std::move(p));
	return pool.back().get();
}

IrExpr* mk_ir_expr(IrExpr&& to_move)
{
	auto& pool = AllocStuff::__ir_expr_pool;

	std::unique_ptr<IrExpr> p;
	p.reset(new IrExpr(std::move(to_move)));

	pool.push_back(std::move(p));
	return pool.back().get();
}

IrCode* mk_linked_ir_code(Function& curr_func)
{
	auto p = mk_unlinked_ir_code();

	relink_ir_code(p, curr_func.ir_code().prev);

	return p;
}
IrCode* mk_linked_ir_code(Function& curr_func, IrInOp s_iop)
{
	auto p = mk_unlinked_ir_code(s_iop);

	relink_ir_code(p, curr_func.ir_code().prev);

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

IrCode* mk_unlinked_ir_code(IrInOp s_iop)
{
	auto p = mk_unlinked_ir_code();
	p->set_iop(s_iop);
	return p;
}
