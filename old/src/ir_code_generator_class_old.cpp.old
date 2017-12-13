#include "ir_code_generator_class.hpp"

#include "../gen_src/grammar.tab.hh"
	extern std::string assign_ident_str;

IrCodeGenerator ircodegen;


IrCodeGenerator::IrCodeGenerator()
{
	__code.next = &__code;
	__code.prev = &__code;
}

IrCodeGenerator::~IrCodeGenerator()
{
	while (__code.next != &__code)
	{
		rmtuple(__code.next);
	}
}

int IrCodeGenerator::ttoi(Tuple* t) const
{
	// Tuple pointer to int position
	int i = 0;
	Tuple* p = __code.next;

	while (p != &__code)
	{
		if (p == t)
		{
			return i;
		}
		++i;
		p = p->next;
	}

	return -1;
}
void IrCodeGenerator::print() const
{
	//for (int i=0; i<__code.size(); ++i)
	for (Tuple* p=__code.next; p!=&__code; p=p->next)
	{
		printout(ttoi(p), ":\t\t");
		switch (p->op)
		{
			case IrCodeOp::Constant:
				printout("const(", p->cval, ")");
				break;
			case IrCodeOp::Load:
				printout("load(", strappcom2(p->vname), ")");
				break;
			case IrCodeOp::Store:
				printout("store(", 
					strappcom2(p->vname, ttoi(p->args[0])), 
					")");
				break;
			case IrCodeOp::LogicalAnd:
				printout("logicand(", 
					strappcom2(ttoi(p->args[0]), ttoi(p->args[1])), 
					")");
				break;
			case IrCodeOp::LogicalOr:
				printout("logicor(", 
					strappcom2(ttoi(p->args[0]), ttoi(p->args[1])), 
					")");
				break;
			case IrCodeOp::CmpEq:
				printout("cmpeq(", 
					strappcom2(ttoi(p->args[0]), ttoi(p->args[1])),
					")");
				break;
			case IrCodeOp::CmpNe:
				printout("cmpne(", 
					strappcom2(ttoi(p->args[0]), ttoi(p->args[1])),
					")");
				break;
			case IrCodeOp::CmpLt:
				printout("cmplt(", 
					strappcom2(ttoi(p->args[0]), ttoi(p->args[1])),
					")");
				break;
			case IrCodeOp::CmpGt:
				printout("cmpgt(", 
					strappcom2(ttoi(p->args[0]), ttoi(p->args[1])),
					")");
				break;
			case IrCodeOp::CmpLe:
				printout("cmple(", 
					strappcom2(ttoi(p->args[0]), ttoi(p->args[1])),
					")");
				break;
			case IrCodeOp::CmpGe:
				printout("cmpge(", 
					strappcom2(ttoi(p->args[0]), ttoi(p->args[1])),
					")");
				break;
			case IrCodeOp::Add:
				printout("add(", 
					strappcom2(ttoi(p->args[0]), ttoi(p->args[1])),
					")");
				break;
			case IrCodeOp::Sub:
				printout("sub(", 
					strappcom2(ttoi(p->args[0]), ttoi(p->args[1])),
					")");
				break;
			case IrCodeOp::Mul:
				printout("mul(", 
					strappcom2(ttoi(p->args[0]), ttoi(p->args[1])),
					")");
				break;
			case IrCodeOp::Div:
				printout("div(", 
					strappcom2(ttoi(p->args[0]), ttoi(p->args[1])),
					")");
				break;
			case IrCodeOp::Mod:
				printout("mod(", 
					strappcom2(ttoi(p->args[0]), ttoi(p->args[1])),
					")");
				break;
			case IrCodeOp::BitwiseAnd:
				printout("bitand(", 
					strappcom2(ttoi(p->args[0]), ttoi(p->args[1])),
					")");
				break;
			case IrCodeOp::BitwiseOr:
				printout("bitor(", 
					strappcom2(ttoi(p->args[0]), ttoi(p->args[1])),
					")");
				break;
			case IrCodeOp::BitwiseXor:
				printout("bitxor(", 
					strappcom2(ttoi(p->args[0]), ttoi(p->args[1])),
					")");
				break;
			case IrCodeOp::Lsl:
				printout("lsl(", 
					strappcom2(ttoi(p->args[0]), ttoi(p->args[1])),
					")");
				break;
			case IrCodeOp::Lsr:
				printout("lsr(", 
					strappcom2(ttoi(p->args[0]), ttoi(p->args[1])),
					")");
				break;
			case IrCodeOp::Asr:
				printout("asr(", 
					strappcom2(ttoi(p->args[0]), ttoi(p->args[1])),
					")");
				break;
			case IrCodeOp::Dummy:
				printout("Eek!");
				break;
		}
		printout("\n");
	}
}


void* IrCodeGenerator::gen_constant(int some_num)
{
	Tuple p;
	p.op = IrCodeOp::Constant;
	p.cval = some_num;
	return mktuple(p);
}
void* IrCodeGenerator::gen_load(const std::string& some_var_name)
{
	Tuple p;
	p.op = IrCodeOp::Load;
	p.vname = some_var_name;
	return mktuple(p);
}

// gen_store() implicitly uses assign_ident_str for the name of the
// destination variable.
void* IrCodeGenerator::gen_store(void* arg)
{
	Tuple p;
	p.op = IrCodeOp::Store;
	p.vname = assign_ident_str;
	p.args[0] = (Tuple*)arg;
	return mktuple(p);
}


// Basically self-explanatory math stuffs
void* IrCodeGenerator::gen_logical_and(void* a, void* b)
{
	return binop(IrCodeOp::LogicalAnd, a, b);
}
void* IrCodeGenerator::gen_logical_or(void* a, void* b)
{
	return binop(IrCodeOp::LogicalOr, a, b);
}
void* IrCodeGenerator::gen_cmp_eq(void* a, void* b)
{
	return binop(IrCodeOp::CmpEq, a, b);
}
void* IrCodeGenerator::gen_cmp_ne(void* a, void* b)
{
	return binop(IrCodeOp::CmpNe, a, b);
}
void* IrCodeGenerator::gen_cmp_lt(void* a, void* b)
{
	return binop(IrCodeOp::CmpLt, a, b);
}
void* IrCodeGenerator::gen_cmp_gt(void* a, void* b)
{
	return binop(IrCodeOp::CmpGt, a, b);
}
void* IrCodeGenerator::gen_cmp_le(void* a, void* b)
{
	return binop(IrCodeOp::CmpLe, a, b);
}
void* IrCodeGenerator::gen_cmp_ge(void* a, void* b)
{
	return binop(IrCodeOp::CmpGe, a, b);
}
void* IrCodeGenerator::gen_add(void* a, void* b)
{
	return binop(IrCodeOp::Add, a, b);
}
void* IrCodeGenerator::gen_sub(void* a, void* b)
{
	return binop(IrCodeOp::Sub, a, b);
}
void* IrCodeGenerator::gen_mul(void* a, void* b)
{
	return binop(IrCodeOp::Mul, a, b);
}
void* IrCodeGenerator::gen_div(void* a, void* b)
{
	return binop(IrCodeOp::Div, a, b);
}
void* IrCodeGenerator::gen_mod(void* a, void* b)
{
	return binop(IrCodeOp::Mod, a, b);
}
void* IrCodeGenerator::gen_bitwise_and(void* a, void* b)
{
	return binop(IrCodeOp::BitwiseAnd, a, b);
}
void* IrCodeGenerator::gen_bitwise_or(void* a, void* b)
{
	return binop(IrCodeOp::BitwiseOr, a, b);
}
void* IrCodeGenerator::gen_bitwise_xor(void* a, void* b)
{
	return binop(IrCodeOp::BitwiseXor, a, b);
}
void* IrCodeGenerator::gen_lsl(void* a, void* b)
{
	return binop(IrCodeOp::Lsl, a, b);
}
void* IrCodeGenerator::gen_lsr(void* a, void* b)
{
	return binop(IrCodeOp::Lsr, a, b);
}
void* IrCodeGenerator::gen_asr(void* a, void* b)
{
	return binop(IrCodeOp::Asr, a, b);
}
