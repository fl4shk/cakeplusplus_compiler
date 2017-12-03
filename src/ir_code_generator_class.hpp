#ifndef ir_code_generator_class_hpp
#define ir_code_generator_class_hpp

#include "misc_includes.hpp"
#include "../gen_src/grammar.tab.hh"
#include "symbol_table_extern_funcs.hpp"


enum class IrCodeOp : int
{
	Constant,
	Load,
	Store,
	LogicalAnd,
	LogicalOr,
	CmpEq,
	CmpNe,
	CmpLt,
	CmpGt,
	CmpLe,
	CmpGe,
	Add,
	Sub,
	Mul,
	Div,
	Mod,
	BitwiseAnd,
	BitwiseOr,
	BitwiseXor,
	Lsl,
	Lsr,
	Asr,

	Dummy
};

class Tuple
{
public:		// variables and constants
	static constexpr size_t max_num_args = 2;

	// Type of operation
	IrCodeOp op = IrCodeOp::Dummy;

	// Argument tuple indices
	Tuple* args[max_num_args];

	// Constant value
	int cval;

	// Ldst variable name
	std::string vname;

	// Linked list stuff
	Tuple * next, * prev;

};


class IrCodeGenerator
{
private:		// variables
	Tuple __code;

public:		// functions
	IrCodeGenerator();
	virtual ~IrCodeGenerator();

	int ttoi(Tuple* t) const;
	void print() const;

	void* gen_constant(int some_num);
	void* gen_load(const std::string& some_var_name);

	// gen_store() implicitly uses assign_ident_str for the destination.
	void* gen_store(void* arg);


	// Basically self-explanatory math stuffs
	void* gen_logical_and(void* a, void* b);
	void* gen_logical_or(void* a, void* b);
	void* gen_cmp_eq(void* a, void* b);
	void* gen_cmp_ne(void* a, void* b);
	void* gen_cmp_lt(void* a, void* b);
	void* gen_cmp_gt(void* a, void* b);
	void* gen_cmp_le(void* a, void* b);
	void* gen_cmp_ge(void* a, void* b);
	void* gen_add(void* a, void* b);
	void* gen_sub(void* a, void* b);
	void* gen_mul(void* a, void* b);
	void* gen_div(void* a, void* b);
	void* gen_mod(void* a, void* b);
	void* gen_bitwise_and(void* a, void* b);
	void* gen_bitwise_or(void* a, void* b);
	void* gen_bitwise_xor(void* a, void* b);
	void* gen_lsl(void* a, void *b);
	void* gen_lsr(void* a, void *b);
	void* gen_asr(void* a, void *b);


protected:		// functions
	inline void* mktuple(const Tuple& to_append)
	{
		//const int ret = __code.size();
		//__code.push_back(to_append);
		//return ret;
		Tuple* p = new Tuple();
		*p = to_append;
		p->next = &__code;
		(p->prev = __code.prev)->next = p;
		return(__code.prev = p);
	}
	inline void rmtuple(Tuple* p)
	{
		__delink_tuple(p);
		delete p;
	}

	inline void __delink_tuple(Tuple* p)
	{
		(p->prev)->next = p->next;
		(p->next)->prev = p->prev;
	}

	inline void* binop(IrCodeOp some_op, void* a, void* b)
	{
		Tuple p;
		p.op = some_op;
		p.args[0] = (Tuple*)a;
		p.args[1] = (Tuple*)b;
		return mktuple(p);
	}
};

extern IrCodeGenerator ircodegen;

#endif		// ir_code_generator_class_hpp
