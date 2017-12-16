#ifndef symbol_table_classes_hpp
#define symbol_table_classes_hpp

#include "misc_includes.hpp"

#include "scoped_ident_table_class.hpp"

#include "vm_code_class.hpp"

enum class SymType : int
{
	//Keyword,
	//BuiltinTypename,


	//// Used by the lexer, fixed by the parser
	//UnknownUserIdent,

	ScalarVarName,
	ArrayVarName,
	//FuncName,
	//StructName,
};

enum class BuiltinTypename : int
{
	Blank,

	//// u8, u16, u32, etc.
	//U8, U16, U32, U64,
	//S8, S16, S32, S64,

	//Int,
	S64,
};


class Symbol
{
private:		// variables
	Ident __name;

	SymType __type;
	BuiltinTypename __var_type;
	//int __val;
	//std::vector<int> __data;
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
	inline Symbol(const Symbol& to_copy) = default;
	inline Symbol(Symbol&& to_move) = default;

	inline Symbol& operator = (const Symbol& to_copy) = default;
	inline Symbol& operator = (Symbol&& to_move) = default;

	gen_getter_and_setter_by_con_ref(name);
	gen_setter_by_rval_ref(name);
	gen_getter_and_setter_by_val(type);
	gen_getter_and_setter_by_val(var_type);
	gen_getter_and_setter_by_val(size);
};


class SymbolTable : public ScopedIdentTable<Symbol>
{
public:		// functions
	SymbolTable();
	virtual ~SymbolTable();
};

class Function
{
private:		// variables
	Ident __name;

	// Local variables and stuff go into each Function's symbol table
	SymbolTable __sym_tbl;

	VmCode __code;


public:		// functions
	inline Function()
	{
		__code.next = &__code;
		__code.prev = &__code;
	}
	inline Function(Ident s_name)
		: __name(s_name)
	{
		__code.next = &__code;
		__code.prev = &__code;
	}
	inline Function(Function&& to_move) = default;

	inline Function& operator = (Function&& to_move) = default;

	gen_getter_and_setter_by_val(name);
	gen_getter_by_ref(sym_tbl);
	//gen_getter_and_setter_by_val(code);
	gen_getter_by_ref(code);
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