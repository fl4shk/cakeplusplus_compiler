#include "code_generator_class.hpp"
#include "frontend_class.hpp"


CodeGenerator::CodeGenerator(Frontend* s_frontend)
	: __frontend(s_frontend)
{
}
CodeGenerator::~CodeGenerator()
{
}
IrCode* CodeGenerator::mk_const(s64 s_simm)
{
	auto ret = mk_unlinked_ir_code(IrOp::Constant);
	ret->simm = s_simm;
	return __frontend->relink_ir_code(ret);
}
IrCode* CodeGenerator::mk_binop(IrUS s_unsgn_or_sgn, 
	IrBinop s_binop, IrCode* a, IrCode* b)
{
	auto ret = mk_unlinked_ir_code(IrOp::Binop);
	ret->unsgn_or_sgn = s_unsgn_or_sgn;
	ret->binop = s_binop;
	ret->args.push_back(a);
	ret->args.push_back(b);

	return __frontend->relink_ir_code(ret);
}
IrCode* CodeGenerator::mk_label(Function& curr_func)
{
	auto ret = mk_unlinked_ir_code(IrOp::Label);

	++curr_func.last_label_num();
	curr_func.num_to_label_map()[curr_func.last_label_num()] = ret;
	
	ret->lab_num = curr_func.last_label_num();

	return __frontend->relink_ir_code(ret);
}
IrCode* CodeGenerator::mk_beq(s64 s_lab_num, IrCode* condition)
{
	auto ret = mk_unlinked_ir_code(IrOp::Beq);

	ret->lab_num = s_lab_num;
	ret->args.push_back(condition);

	return __frontend->relink_ir_code(ret);
}
IrCode* CodeGenerator::mk_bne(s64 s_lab_num, IrCode* condition)
{
	auto ret = mk_unlinked_ir_code(IrOp::Bne);

	ret->lab_num = s_lab_num;
	ret->args.push_back(condition);

	return __frontend->relink_ir_code(ret);
}
IrCode* CodeGenerator::mk_jump(s64 s_lab_num)
{
	auto ret = mk_unlinked_ir_code(IrOp::Jump);

	ret->lab_num = s_lab_num;

	return __frontend->relink_ir_code(ret);
}
IrCode* CodeGenerator::mk_address(Symbol* s_sym)
{
	auto ret = mk_unlinked_ir_code(IrOp::Address);

	ret->sym = s_sym;

	return __frontend->relink_ir_code(ret);
}
IrCode* CodeGenerator::mk_address(Function* s_func)
{
	auto ret = mk_unlinked_ir_code(IrOp::Address);

	ret->func = s_func;

	return __frontend->relink_ir_code(ret);
}
IrCode* CodeGenerator::mk_ldx(IrUS s_unsgn_or_sgn, 
	IrLdStSize s_ldst_size, IrCode* addr, IrCode* index)
{
	auto ret = mk_unlinked_ir_code(IrOp::Ldx);

	ret->unsgn_or_sgn = s_unsgn_or_sgn;
	ret->ldst_size = s_ldst_size;
	ret->args.push_back(addr);
	ret->args.push_back(index);

	return __frontend->relink_ir_code(ret);
}
IrCode* CodeGenerator::mk_stx(IrUS s_unsgn_or_sgn, 
	IrLdStSize s_ldst_size, IrCode* addr, IrCode* index, IrCode* data)
{
	auto ret = mk_unlinked_ir_code(IrOp::Stx);

	ret->unsgn_or_sgn = s_unsgn_or_sgn;
	ret->ldst_size = s_ldst_size;
	ret->args.push_back(addr);
	ret->args.push_back(index);
	ret->args.push_back(data);

	return __frontend->relink_ir_code(ret);
}
IrCode* CodeGenerator::mk_unfinished_call()
{
	auto ret = mk_unlinked_ir_code(IrOp::Call);

	return ret;
}
IrCode* CodeGenerator::mk_ret_expr(IrCode* expr)
{
	auto ret = mk_unlinked_ir_code(IrOp::RetExpr);

	ret->args.push_back(expr);

	return __frontend->relink_ir_code(ret);
}
IrCode* CodeGenerator::mk_ret_nothing()
{
	auto ret = mk_unlinked_ir_code(IrOp::RetNothing);

	return __frontend->relink_ir_code(ret);
}
IrCode* CodeGenerator::mk_syscall
	(IrSyscallShorthandOp s_syscall_shorthand_op)
{
	auto ret = mk_unlinked_ir_code(IrOp::Syscall);

	ret->syscall_shorthand_op = s_syscall_shorthand_op;

	return __frontend->relink_ir_code(ret);
}
IrCode* CodeGenerator::mk_quit(IrCode* expr)
{
	auto ret = mk_unlinked_ir_code(IrOp::Quit);

	ret->args.push_back(expr);

	return __frontend->relink_ir_code(ret);
}
