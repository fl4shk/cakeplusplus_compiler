#ifndef allocation_stuff_hpp
#define allocation_stuff_hpp

#include "misc_includes.hpp"

//#include "symbol_table_classes.hpp"
#include "vm_code_class.hpp"
//#include "ir_code_classes.hpp"
#include "ir_code_stuff.hpp"

#include <map>

class Function;
class Var;
class VmCode;

class AllocStuff
{
	friend int* cstm_intdup(int to_dup);
	friend std::string* cstm_strdup(const std::string& to_dup);

	friend Var* mk_var();
	friend Var* mk_var(Ident s_name, BuiltinTypename s_type, 
		size_t s_size, Function* s_func);

	//friend VmCode* append_vm_code(Function& func);
	//friend AstNode* mk_ast_node();
	//friend VmCode* append_vm_code(VmCode& some_head);
	friend VmCode* mk_unlinked_vm_code();


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
	static std::vector<std::unique_ptr<VmCode>> __vm_code_pool;
	static std::vector<std::unique_ptr<IrExpr>> __ir_expr_pool;
	static std::vector<std::unique_ptr<IrCode>> __ir_code_pool;
	//static std::vector<std::unique_ptr<AstNode>> __ast_node_pool;

};

int* cstm_intdup(int to_dup);
std::string* cstm_strdup(const std::string& to_dup);

Var* mk_var();
Var* mk_var(Ident s_name, BuiltinTypename s_type, size_t s_size, 
	Function* s_func);

//VmCode* append_vm_code(VmCode& some_head);
VmCode* mk_linked_vm_code(VmCode& some_head);
VmCode* mk_linked_vm_code(VmCode& some_head, VmRawInstrOp s_raw_op);
VmCode* mk_unlinked_vm_code();
VmCode* mk_unlinked_vm_code(VmRawInstrOp s_raw_op);
inline VmCode* relink_vm_code(VmCode* p, VmCode* to_link_after)
{
	VmCode* old_next = to_link_after->next;

	to_link_after->next = p;
	p->prev = to_link_after;
	p->next = old_next;
	old_next->prev = p;

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
