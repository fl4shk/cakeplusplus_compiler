#ifndef symbol_table_classes_hpp
#define symbol_table_classes_hpp

#include "misc_includes.hpp"

#include "scoped_ident_table_class.hpp"
#include "symbol_table_base_class.hpp"

#include "vm_code_class.hpp"
#include "ir_code_classes.hpp"
#include "allocation_stuff.hpp"

enum class SymType : int
{
	ScalarVarName,
	ArrayVarName,
	//FuncName,
	//ClassName,
};

enum class BuiltinTypename : int
{
	Blank,

	// u8, u16, u32, etc.
	U8, U16, U32, U64,
	S8, S16, S32, S64,
};


class Symbol
{
private:		// variables
	Ident __name;

	SymType __type;
	BuiltinTypename __var_type;



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
	size_t __size;


public:		// functions
	inline Symbol()
	{
	}
	inline Symbol(Ident s_name, SymType s_type,
		BuiltinTypename s_var_type, size_t s_size)
		: __name(s_name), __type(s_type), __var_type(s_var_type),
		__size(s_size)
	{
	}
	inline Symbol(Ident s_name, SymType s_type,
		BuiltinTypename s_var_type, bool s_is_arg, size_t s_size)
		: __name(s_name), __type(s_type), __var_type(s_var_type),
		__is_arg(s_is_arg), __size(s_size)
	{
	}
	inline Symbol(const Symbol& to_copy) = default;
	inline Symbol(Symbol&& to_move) = default;

	inline Symbol& operator = (const Symbol& to_copy) = default;
	inline Symbol& operator = (Symbol&& to_move) = default;

	gen_getter_and_setter_by_con_ref(name);
	gen_setter_by_rval_ref(name);
	gen_getter_and_setter_by_val(type);
	gen_getter_and_setter_by_val(var_type);
	gen_getter_and_setter_by_val(is_arg);
	gen_getter_and_setter_by_val(offset);
	gen_getter_and_setter_by_val(size);
};


class SymbolTable : public SymbolTableBase<Symbol>
{
public:		// functions
	SymbolTable();
	virtual ~SymbolTable();
};

class Function
{
private:		// variables
	Ident __name;


	// Function arguments go into the first scope of the symbol table
	// 
	// Local variables go into each Function's symbol table
	SymbolTable __sym_tbl;

	VmCode __vm_code;
	IrCode __ir_code;

	// Label numbering stuff
	s64 __last_label_num = -1;
	std::map<s64, IrCode*> __num_to_label_map;

	size_t __last_arg_offset = -1;



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
	inline Function(Function&& to_move) = default;

	inline Function& operator = (Function&& to_move) = default;

	inline VmCode* append_vm_code()
	{
		return ::append_vm_code(__vm_code);
	}

	inline IrCode* append_ir_code()
	{
		auto ret = ::append_ir_code(__ir_code);
		ret->func = this;
		return ret;
	}

	s64 irntoi(IrCode* t) const;

	gen_getter_and_setter_by_val(name);
	gen_getter_by_ref(sym_tbl);
	gen_getter_by_ref(vm_code);
	gen_getter_by_ref(ir_code);
	gen_getter_by_ref(last_label_num);
	gen_getter_by_ref(num_to_label_map);
	gen_getter_by_ref(last_arg_offset);
};

class FunctionTable : public IdentTable<Function>
{
public:		// functions
	FunctionTable();
	virtual ~FunctionTable();
};


//std::ostream& operator << (std::ostream& os, const SymType& to_print);

//extern SymbolTable sym_tbl;

#endif		// symbol_table_classes_hpp
