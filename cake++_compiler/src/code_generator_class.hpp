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
	inline auto mk_binop(IrBinop s_binop, IrCode* a, IrCode* b)
	{
		return mk_binop(IrUS::Sgn, s_binop, a, b);
	}

	// Make a label that isn't linked into the Function's __ir_code yet but
	// still uses the label numbers from that Function.
	IrCode* mk_unlinked_label();
	IrCode* mk_label();
	IrCode* mk_beq(s64 s_lab_num, IrCode* condition);
	inline auto mk_beq(IrCode* label, IrCode* condition)
	{
		return mk_beq(label->lab_num, condition);
	}
	IrCode* mk_bne(s64 s_lab_num, IrCode* condition);
	inline auto mk_bne(IrCode* label, IrCode* condition)
	{
		return mk_bne(label->lab_num, condition);
	}

	inline auto mk_branch_if_false(s64 s_lab_num, IrCode* condition)
	{
		return mk_beq(s_lab_num, condition);
	}
	inline auto mk_branch_if_false(IrCode* label, IrCode* condition)
	{
		return mk_beq(label, condition);
	}
	inline auto mk_branch_if_true(s64 s_lab_num, IrCode* condition)
	{
		return mk_bne(s_lab_num, condition);
	}
	inline auto mk_branch_if_true(IrCode* label, IrCode* condition)
	{
		return mk_bne(label, condition);
	}

	IrCode* mk_bra(s64 s_lab_num);
	inline auto mk_bra(IrCode* label)
	{
		return mk_bra(label->lab_num);
	}
	IrCode* mk_jump(s64 s_lab_num);
	inline auto mk_jump(IrCode* label)
	{
		return mk_jump(label->lab_num);
	}
	IrCode* mk_address(Symbol* s_sym);
	IrCode* mk_address(Function* s_func);
	IrCode* mk_ldx(IrUS s_unsgn_or_sgn, IrLdStSize s_ldst_size, 
		IrCode* addr, IrCode* index);
	inline auto mk_ldx(IrCode* addr, IrCode* index)
	{
		return mk_ldx(IrUS::Sgn, IrLdStSize::Sz64, addr, index);
	}
	IrCode* mk_stx(IrUS s_unsgn_or_sgn, IrLdStSize s_ldst_size, 
		IrCode* addr, IrCode* index, IrCode* data);
	inline auto mk_stx(IrCode* addr, IrCode* index, IrCode* data)
	{
		return mk_stx(IrUS::Sgn, IrLdStSize::Sz64, addr, index, data);
	}

	// Unfinished call because we don't know how many arguments there
	// are in the code generator.
	IrCode* mk_unfinished_call();

	IrCode* mk_ret_expr(IrCode* expr);
	IrCode* mk_ret_nothing();
	IrCode* mk_syscall(IrSyscallShorthandOp s_syscall_shorthand_op);
	IrCode* mk_quit(IrCode* expr);

	inline auto mk_log_not(IrCode* expr)
	{
		return mk_binop(IrBinop::CmpNe, expr, mk_const(0));
	}
};


#endif		// code_generator_class_hpp
