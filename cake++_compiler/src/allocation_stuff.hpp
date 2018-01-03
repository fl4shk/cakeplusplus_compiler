#ifndef allocation_stuff_hpp
#define allocation_stuff_hpp

#include "misc_includes.hpp"

//#include "symbol_table_classes.hpp"
#include "backends/backend_code_base_class.hpp"
//#include "ir_code_classes.hpp"
#include "ir_code_stuff.hpp"

#include <map>

class Function;
class Var;

class AllocStuff
{
	friend int* cstm_intdup(int to_dup);
	friend std::string* cstm_strdup(const std::string& to_dup);

	friend Var* mk_var();
	friend Var* mk_var(Ident s_name, BuiltinTypename s_type, 
		size_t s_size, Function* s_func);

	template<typename Type>
	friend inline BackendCodeBase* mk_unlinked_backend_base_code();


	friend IrExpr* mk_ir_pure_expr(IrPureExOp s_op, IrMachineMode s_mm);
	friend IrExpr* mk_ir_pure_expr(IrPureExOp s_op, IrMachineMode s_mm, 
		IrExpr* some_parent);
	friend IrExpr* mk_ir_spec_expr(IrSpecExOp s_op, IrMachineMode s_mm);
	friend IrExpr* mk_ir_spec_expr(IrSpecExOp s_op, IrMachineMode s_mm, 
		IrExpr* some_parent);
	friend IrExpr* mk_ir_expr(IrExpr&& to_move);

	//friend IrCode* append_ir_code(IrCode& some_head);
	friend IrCode* mk_unlinked_ir_code();

private:			// static variables
	static std::map<int, std::unique_ptr<int>> __int_pool;
	static std::map<std::string, std::unique_ptr<std::string>> __str_pool;

	static std::vector<std::unique_ptr<Var>> __var_pool;
	static std::vector<std::unique_ptr<BackendCodeBase>>
		__backend_code_base_pool;
	static std::vector<std::unique_ptr<IrExpr>> __ir_expr_pool;
	static std::vector<std::unique_ptr<IrCode>> __ir_code_pool;

};

int* cstm_intdup(int to_dup);
std::string* cstm_strdup(const std::string& to_dup);

Var* mk_var();
Var* mk_var(Ident s_name, BuiltinTypename s_type, size_t s_size, 
	Function* s_func);


inline BackendCodeBase* relink_backend_base_code(BackendCodeBase* p, 
	BackendCodeBase* to_link_after);
template<typename Type>
inline BackendCodeBase* mk_unlinked_backend_base_code();
template<typename Type>
inline BackendCodeBase* mk_linked_backend_base_code
	(BackendCodeBase* some_head)
{
	auto p = mk_unlinked_backend_base_code<Type>();

	relink_backend_base_code(static_cast<BackendCodeBase*>(p),
		some_head->prev);

	return p;
}
template<typename Type>
inline BackendCodeBase* mk_unlinked_backend_base_code()
{
	auto& pool = AllocStuff::__backend_code_base_pool;

	std::unique_ptr<BackendCodeBase> p;
	p.reset(new Type());

	pool.push_back(std::move(p));

	return pool.back().get();
}
inline BackendCodeBase* relink_backend_base_code(BackendCodeBase* p, 
	BackendCodeBase* to_link_after)
{
	BackendCodeBase* old_next = to_link_after->next;

	to_link_after->next = p;
	p->prev = to_link_after;
	p->next = old_next;
	old_next->prev = p;

	return p;
}
inline auto delink_backend_code_base(BackendCodeBase* p)
{
	auto old_next = p->next;
	auto old_prev = p->prev;

	p->next = nullptr;
	p->prev = nullptr;

	old_next->prev = old_prev;
	old_prev->next = old_next;

	return p;
}

IrExpr* mk_ir_pure_expr(IrPureExOp s_op, IrMachineMode s_mm);
IrExpr* mk_ir_pure_expr(IrPureExOp s_op, IrMachineMode s_mm, 
	IrExpr* some_parent);
IrExpr* mk_ir_spec_expr(IrSpecExOp s_op, IrMachineMode s_mm);
IrExpr* mk_ir_spec_expr(IrSpecExOp s_op, IrMachineMode s_mm, 
	IrExpr* some_parent);
IrExpr* mk_ir_expr(IrExpr&& to_move);

//IrCode* append_ir_code(IrCode& some_head);
IrCode* mk_linked_ir_code(Function& curr_func);
IrCode* mk_linked_ir_code(Function& curr_func, IrInOp s_iop);
IrCode* mk_unlinked_ir_code();
IrCode* mk_unlinked_ir_code(IrInOp s_iop);
inline IrCode* relink_ir_code(IrCode* p, IrCode* to_link_after)
{
	IrCode* old_next = to_link_after->next;

	to_link_after->next = p;
	p->prev = to_link_after;
	p->next = old_next;
	old_next->prev = p;

	return p;
}


#endif		// allocation_stuff_hpp
