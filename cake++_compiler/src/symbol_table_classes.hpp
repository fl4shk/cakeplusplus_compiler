#ifndef symbol_table_classes_hpp
#define symbol_table_classes_hpp

#include "misc_includes.hpp"

#include "scoped_ident_table_class.hpp"
#include "symbol_table_base_class.hpp"

#include "vm_code_class.hpp"
//#include "ir_code_classes.hpp"
#include "ir_code_stuff.hpp"
#include "allocation_stuff.hpp"

enum class SymType : u32
{
	ScalarVarName,
	ArrayVarName,
	FuncName,
	//ClassName,
	////ScalarClassInstName,
	////ArrayClassInstName,
};

enum class BuiltinTypename : u32
{
	Blank,

	U64,
	S64,

	U32,
	S32,

	U16,
	S16,

	U8,
	S8,
};

std::ostream& operator << (std::ostream& os, 
	BuiltinTypename some_builtin_typename);

//class Function;

class Var
{
private:		// variables
	Ident __name;

	// Should be replaced with a pointer to a class repressenting typenames
	BuiltinTypename __type;


	// Which argument
	size_t __arg_offset = 0;

	// If this is an argument to the function
	bool __is_arg = false;


	// Offset for "argx" or "varx".  If this is zero, then we can use the
	// "arg" or "var" instruction.
	// 
	// For local variable arrays or classes, this is the offset for the
	// start of the array or class.
	// 
	// However, argument arrays and classes are passed by reference.
	s64 __offset = 0;


	// Dimensions
	size_t __size = 1;


public:		// functions
	inline Var()
	{
	}
	inline Var(Ident s_name, BuiltinTypename s_type, size_t s_size)
		: __name(s_name), __type(s_type), __size(s_size)
	{
	}
	inline Var(const Var& to_copy) = default;
	inline Var(Var&& to_move) = default;

	inline Var& operator = (const Var& to_copy) = default;
	inline Var& operator = (Var&& to_move) = default;

	bool is_unsgn_builtin() const;
	bool is_sgn_builtin() const;

	inline bool has_builtin_var_type() const
	{
		return (is_unsgn_builtin() || is_sgn_builtin());
	}

	s64 builtin_type_size() const;

	//inline IrUS get_unsgn_or_sgn() const
	//{
	//	return is_unsgn_builtin() ? IrUS::Unsgn : IrUS::Sgn;
	//}
	//IrLdStSize get_ldst_size() const;

	gen_getter_and_setter_by_con_ref(name);
	gen_setter_by_rval_ref(name);
	gen_getter_and_setter_by_val(type);
	gen_getter_and_setter_by_val(arg_offset);
	gen_getter_and_setter_by_val(is_arg);
	gen_getter_and_setter_by_val(offset);
	gen_getter_and_setter_by_val(size);
};

class Symbol
{
private:		// variables
	SymType __type;

	union
	{
		Var* __var;
		Function* __func;
	};

public:		// functions
	inline Symbol()
	{
	}
	inline Symbol(SymType s_type, Var* s_var)
		: __type(s_type), __var(s_var)
	{
	}
	inline Symbol(Function* s_func)
		: __type(SymType::FuncName), __func(s_func)
	{
	}

	inline Symbol(const Symbol& to_copy) = default;
	Symbol& operator = (const Symbol& to_copy) = default;
	
	gen_getter_and_setter_by_val(type);
	gen_getter_and_setter_by_val(var);
	gen_getter_and_setter_by_val(func);

	// name() and set_name() passthroughs
	Ident name() const;
	void set_name(Ident s_name);
};


class SymbolTable : public SymbolTableBase<Symbol>
{
public:		// functions
	SymbolTable();
	virtual ~SymbolTable();
};

class FunctionTable;

class Function
{
public:		// class

private:		// variables
	Ident __name;


	// Function arguments go into the first scope of the symbol table
	// 
	// Local variables go into each Function's symbol table
	SymbolTable __sym_tbl;

	VmCode __vm_code;
	IrCode __ir_code;
	//IrCode __ir_code;

	// Label numbering stuff
	s64 __last_label_num = -1;
	std::map<s64, IrCode*> __num_to_label_map;

	// Argument ordering stuff (used by Frontend::visitFuncArgDecl())
	size_t __last_arg_offset = -1;


	//std::set<VmCode*> __unfinished_func_refs_set;

	BuiltinTypename __ret_type = BuiltinTypename::S64;



public:		// functions
	inline Function()
	{
		__vm_code.next = &__vm_code;
		__vm_code.prev = &__vm_code;
		__ir_code.next = &__ir_code;
		__ir_code.prev = &__ir_code;
	}
	inline Function(Ident s_name)
		: __name(s_name)
	{
		__vm_code.next = &__vm_code;
		__vm_code.prev = &__vm_code;
		__ir_code.next = &__ir_code;
		__ir_code.prev = &__ir_code;
	}

	//inline Function(const Function& to_copy) = default;
	inline Function(Function&& to_move) = default;

	//inline Function& operator = (const Function& to_copy) = default;
	//inline Function& operator = (Function&& to_move) = default;

	std::vector<Symbol*> get_args() const;
	//Symbol* get_one_arg(size_t some_arg_offset) const;

	//inline VmCode* append_vm_code()
	//{
	//	return ::append_vm_code(__vm_code);
	//}
	//VmCode* append_vm_code(VmRawInstrOp s_raw_op);

	//inline IrCode* append_ir_code()
	//{
	//	auto ret = ::append_ir_code(__ir_code);
	//	ret->func = this;
	//	return ret;
	//}

	//s64 irntoi(IrCode* t) const;
	s64 offset_of_vm_code(VmCode* v) const;

	void gen_vm_code();
	//void adjust_vm_code();
	std::ostream& osprint_vm_code(std::ostream& os);

	gen_getter_and_setter_by_val(name);
	gen_getter_by_ref(sym_tbl);
	gen_getter_by_ref(vm_code);
	//gen_getter_by_ref(ir_code);
	gen_getter_by_ref(ir_code);
	gen_getter_by_ref(last_label_num);
	gen_getter_by_ref(num_to_label_map);
	gen_getter_by_ref(last_arg_offset);
	gen_getter_and_setter_by_val(ret_type);

private:		// functions
	inline VmCode* mk_linked_vm_code(VmRawInstrOp s_raw_op)
	{
		return ::mk_linked_vm_code(__vm_code, s_raw_op);
	}
	//inline VmCode* mk_unlinked_vm_code(VmRawInstrOp s_raw_op)
	//{
	//	return ::mk_unlinked_vm_code(s_raw_op);
	//}
	//inline void relink_vm_code(VmCode* p)
	//{
	//	::relink_vm_code(p, __vm_code.prev);
	//}


};

class FunctionTable : public IdentToPointerTable<Function>
{
public:		// functions
	FunctionTable();
	virtual ~FunctionTable();
};


//std::ostream& operator << (std::ostream& os, const SymType& to_print);

//extern SymbolTable sym_tbl;

#endif		// symbol_table_classes_hpp
