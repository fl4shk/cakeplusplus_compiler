#ifndef code_generator_class_hpp
#define code_generator_class_hpp


#include "symbol_table_classes.hpp"
//#include "abstract_syntax_tree_classes.hpp"
#include "vm_code_class.hpp"
#include "ir_code_classes.hpp"

class Frontend;

class CodeGenerator
{
protected:		// variables
	Frontend* __frontend;

public:		// functions
	CodeGenerator(Frontend* s_frontend);
	virtual ~CodeGenerator();

	IrCode* mk_const(s64 s_simm);
	IrCode* mk_binop(IrUS s_unsgn_or_sgn, IrBinop s_binop, IrCode* a, 
		IrCode* b);
	IrCode* mk_label(Function& curr_func);
	IrCode* mk_beq(s64 s_lab_num, IrCode* condition);
	IrCode* mk_bne(s64 s_lab_num, IrCode* condition);
	IrCode* mk_jump(s64 s_lab_num);
	IrCode* mk_address(Symbol* s_sym);
	IrCode* mk_address(Function* s_func);
	IrCode* mk_ldx(IrUS s_unsgn_or_sgn, IrLdStSize s_ldst_size, 
		IrCode* addr, IrCode* index);
	IrCode* mk_stx(IrUS s_unsgn_or_sgn, IrLdStSize s_ldst_size, 
		IrCode* addr, IrCode* index, IrCode* data);

	// Unfinished call because we don't know how many arguments there
	// are in the code generator.
	IrCode* mk_unfinished_call();

	IrCode* mk_ret_expr(IrCode* expr);
	IrCode* mk_ret_nothing();
	IrCode* mk_syscall(IrSyscallShorthandOp s_syscall_shorthand_op);
	IrCode* mk_quit(IrCode* expr);
};


#endif		// code_generator_class_hpp
