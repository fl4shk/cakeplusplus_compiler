#ifndef code_generator_class_hpp
#define code_generator_class_hpp


#include "symbol_table_classes.hpp"
//#include "abstract_syntax_tree_classes.hpp"
#include "vm_code_class.hpp"
//#include "ir_code_classes.hpp"
#include "ir_code_stuff.hpp"

class Frontend;

class CodeGenerator
{
protected:		// variables
	Frontend* __frontend;

public:		// functions
	CodeGenerator(Frontend* s_frontend);
	virtual ~CodeGenerator();


	IrExpr* mk_expr_constant(IrMachineMode s_mm, s64 s_simm);
	IrExpr* mk_expr_binop(IrMachineMode s_mm, IrBinop s_binop, 
		IrExpr* a, IrExpr* b);
	//IrExpr* mk_expr_binop(IrBinop s_binop, IrExpr* a, IrExpr* b);
	IrExpr* mk_expr_unop(IrMachineMode s_mm, IrUnop s_unop, IrExpr* a);
	IrExpr* mk_expr_ref_sym(Symbol* s_sym);
	IrExpr* mk_expr_ref_func(Function* s_func);
	IrExpr* mk_expr_ref_lab(s64 s_lab_num);
	IrExpr* mk_expr_len(IrMachineMode s_mm, IrExpr* what);
	IrExpr* mk_expr_sizeof(IrMachineMode s_mm, IrExpr* what);
	IrExpr* mk_expr_unfinished_call_with_ret(IrMachineMode s_mm,
		IrExpr* where);
	IrExpr* mk_expr_address(IrExpr* where);
	IrExpr* mk_expr_ld(IrMachineMode s_mm, IrExpr* where);
	IrExpr* mk_expr_get_next_pc();
	IrExpr* mk_expr_if_then_else(IrMachineMode s_mm, IrExpr* cond, 
		IrExpr* what_if, IrExpr* what_else);
	inline IrExpr* mk_expr_if_then_else(IrExpr* cond,
		IrExpr* what_if, s64 what_else_lab_num)
	{
		return mk_expr_if_then_else(IrMachineMode::Pointer, cond, what_if, 
			mk_expr_address(mk_expr_ref_lab(what_else_lab_num)));
	}
	inline IrExpr* mk_expr_if_then_else(IrExpr* cond,
		s64 what_if_lab_num, s64 what_else_lab_num)
	{
		return mk_expr_if_then_else(IrMachineMode::Pointer, cond, 
			mk_expr_address(mk_expr_ref_lab(what_if_lab_num)),
			mk_expr_address(mk_expr_ref_lab(what_else_lab_num)));
	}
	IrExpr* mk_expr_cast(IrMachineMode s_mm, IrExpr* expr);

	IrCode* mk_code_st(IrMachineMode s_st_mm, IrExpr* where, 
		IrExpr* what);
	IrCode* mk_code_return_expr(IrExpr* expr);
	IrCode* mk_code_return_nothing();
	IrCode* mk_code_quit(IrExpr* val);
	IrCode* mk_code_jump(IrExpr* where);
	//IrCode* mk_code_unfinished_call(IrExpr* where);
	IrCode* mk_code_call(IrExpr* call_expr);
	IrCode* mk_code_unfinished_syscall
		(IrSyscallShorthandOp s_syscall_shorthand_op);
	IrCode* mk_code_unlinked_label();
	IrCode* mk_code_linked_label();

	

	//std::ostream& osprint_func_ir_code(std::ostream& os,
	//	Function& curr_func);
	void output_func_ir_code_as_json(Json::Value& output_root,
		Function& curr_func);

protected:		// functions
	IrCode* mk_linked_ir_code(IrInOp s_iop);

	//std::ostream& osprint_ir_expr(std::ostream& os, IrExpr* p);
	void output_ir_expr_as_json(Json::Value& node, IrExpr* p);

	inline std::string get_label_name(IrCode* some_label) const
	{
		return get_label_name(some_label->lab_num());
	}
	std::string get_label_name(s64 some_lab_num) const;


};


#endif		// code_generator_class_hpp
