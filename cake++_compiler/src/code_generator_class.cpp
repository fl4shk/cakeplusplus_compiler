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
IrCode* CodeGenerator::mk_unlinked_label()
{
	auto ret = mk_unlinked_ir_code(IrOp::Label);

	auto& curr_func = __frontend->curr_func();

	++curr_func.last_label_num();
	curr_func.num_to_label_map()[curr_func.last_label_num()] = ret;
	
	ret->lab_num = curr_func.last_label_num();

	//return __frontend->relink_ir_code(ret);
	return ret;
}
IrCode* CodeGenerator::mk_label()
{
	return __frontend->relink_ir_code(mk_unlinked_label());
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
IrCode* CodeGenerator::mk_bra(s64 s_lab_num)
{
	auto ret = mk_unlinked_ir_code(IrOp::Bra);

	ret->lab_num = s_lab_num;

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

std::ostream& CodeGenerator::osprint_func(std::ostream& os, 
	Function& curr_func)
{
	for (auto p=curr_func.ir_code().next;
		p!=&curr_func.ir_code();
		p=p->next)
	{
		osprintout(os, curr_func.irntoi(p), "\t");
		switch (p->op)
		{
			// Constant number
			case IrOp::Constant:
				osprintout(os, "const(", p->simm, ")");
				break;


			// Binary operator
			case IrOp::Binop:
				switch(p->binop)
				{
					case IrBinop::Add:
						osprintout(os, "add");
						break;
					case IrBinop::Sub:
						osprintout(os, "sub");
						break;
					case IrBinop::Mul:
						osprintout(os, "mul");
						break;
					case IrBinop::Div:
						osprintout(os, "div");
						break;
					case IrBinop::Mod:
						osprintout(os, "mod");
						break;

					case IrBinop::BitAnd:
						osprintout(os, "bit_and");
						break;
					case IrBinop::BitOr:
						osprintout(os, "bit_or");
						break;
					case IrBinop::BitXor:
						osprintout(os, "bit_xor");
						break;

					case IrBinop::BitLsl:
						osprintout(os, "bit_lsl");
						break;
					case IrBinop::BitLsr:
						osprintout(os, "bit_lsr");
						break;
					case IrBinop::BitAsr:
						osprintout(os, "bit_asr");
						break;

					case IrBinop::CmpEq:
						osprintout(os, "cmp_eq");
						break;
					case IrBinop::CmpNe:
						osprintout(os, "cmp_ne");
						break;
					case IrBinop::CmpLt:
						osprintout(os, "cmp_lt");
						break;
					case IrBinop::CmpLe:
						osprintout(os, "cmp_ge");
						break;

					default:
						printerr("CodeGenerator::osprint_func():  ",
							"Binop Eek!\n");
						exit(1);
				}
				osprintout(os, 
					"(", strappcom2(curr_func.irntoi(p->args.at(0)),
					curr_func.irntoi(p->args.at(1))), ")");
				break;


			// Label, given a number
			case IrOp::Label:
				osprintout(os, "label(", p->lab_num, ")");
				break;

			// Conditional branch to a label
			case IrOp::Beq:
				osprintout(os, "beq(", strappcom2(p->lab_num,
					curr_func.irntoi(p->args.at(0))), ")");
				break;
			case IrOp::Bne:
				osprintout(os, "bne(", strappcom2(p->lab_num,
					curr_func.irntoi(p->args.at(0))), ")");
				break;

			// Unconditional branch to a label
			case IrOp::Bra:
				osprintout(os, "bra(", p->lab_num, ")");
				break;


			// Unconditional jump to a label
			case IrOp::Jump:
				osprintout(os, "jump(", p->lab_num, ")");
				break;



			// Address of symbol or function
			case IrOp::Address:
				osprintout(os, "address(");
				if (p->func)
				{
					osprintout(os, *p->func->name());
				}
				else if (p->sym)
				{
					osprintout(os, *p->sym->name());
				}
				else
				{
					printerr("CodeGenerator::osprint_func():  ",
						"address Eek!\n");
					exit(1);
				}
				osprintout(os, ")");
				break;


			// Indexed load or store
			// Load indexed
			case IrOp::Ldx:
				osprintout(os, "ldx(", strappcom2
					(curr_func.irntoi(p->args.at(0)),
					curr_func.irntoi(p->args.at(1))), ")");
				break;

			// Store indexed 
			case IrOp::Stx:
				osprintout(os, "stx(", strappcom2
					(curr_func.irntoi(p->args.at(0)),
					curr_func.irntoi(p->args.at(1)),
					curr_func.irntoi(p->args.at(2))), ")");
				break;

			// Function call (takes an address address)
			case IrOp::Call:
				osprintout(os, "call(", 
					curr_func.irntoi(p->args.at(0)), "(");
				for (size_t i=1; i<p->args.size(); ++i)
				{
					osprintout(os, curr_func.irntoi(p->args.at(i)));

					if ((i + 1) != p->args.size())
					{
						osprintout(os, ", ");
					}
				}
				osprintout(os, "))");
				break;

			// return expr;
			case IrOp::RetExpr:
				break;

			// return;
			case IrOp::RetNothing:
				osprintout(os, "ret_nothing");
				break;


			// System call
			case IrOp::Syscall:
				osprintout(os, "syscall",
					"(", curr_func.irntoi(p->args.at(0)), ")");
				break;

			case IrOp::Quit:
				osprintout(os, "quit",
					"(", curr_func.irntoi(p->args.at(0)), ")");
				break;

			default:
				printerr("CodeGenerator::osprint_func():  Op Eek!\n");
				exit(1);
		}

		osprintout(os, "\n");
	}

	return os;
}
