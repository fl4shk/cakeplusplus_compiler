#ifndef symbol_table_class_hpp
#define symbol_table_class_hpp

#include "misc_includes.hpp"

#include "scoped_ident_table_class.hpp"

enum class SymType : int
{
	//Keyword,
	//BuiltinTypename,


	//// Used by the lexer, fixed by the parser
	//UnknownUserIdent,

	ScalarVarName,
	ArrayVarName,
	FuncName,
	//StructName,
};

enum class BuiltinTypename : int
{
	Blank,

	//// u8, u16, u32, etc.
	//U8, U16, U32, U64,
	//S8, S16, S32, S64,

	Int,
};


class Symbol
{
private:		// variables
	std::string __name;

	SymType __type;
	BuiltinTypename __var_type;
	//int __val;
	std::vector<int> __data;

public:		// functions
	inline Symbol()
	{
	}
	inline Symbol(const std::string& s_name, SymType s_type,
		BuiltinTypename s_var_type)
		: __name(s_name), __type(s_type), __var_type(s_var_type)
	{
	}
	inline Symbol(const Symbol& to_copy) = default;
	inline Symbol(Symbol&& to_move) = default;

	inline Symbol& operator = (const Symbol& to_copy) = default;
	inline Symbol& operator = (Symbol&& to_move) = default;

	inline auto size() const
	{
		return __data.size();
	}

	gen_getter_and_setter_by_con_ref(name);
	gen_setter_by_rval_ref(name);
	gen_getter_and_setter_by_val(type);
	gen_getter_and_setter_by_val(var_type);
	gen_getter_by_ref(data);
};

//typedef IdentTable<Symbol> SymbolTable;
//typedef ScopedIdentTable<Symbol> SymbolTable;


class SymbolTable : public ScopedIdentTable<Symbol>
{
public:		// functions
	SymbolTable();
	virtual ~SymbolTable();

	//void debug_print() __attribute__((noinline))
	//{
	//	for (size_t i=0; i<table().size(); ++i)
	//	{
	//		auto& outer_iter = table().at(i);
	//		for (const auto& inner_iter : outer_iter.table())
	//		{
	//			printout("level ", i, ":  \"", inner_iter.first, "\":  ", 
	//				inner_iter.second.tok()->str(), ", ", 
	//				inner_iter.second.type(), "\n");
	//		}
	//	}
	//}

	//void debug_print_old() __attribute__((noinline))
	//{
	//	for (size_t i=0; i<__old_table.size(); ++i)
	//	{
	//		auto& outer_iter = __old_table.at(i);
	//		for (const auto& inner_iter : outer_iter.table())
	//		{
	//			printout("level ", i, ":  \"", inner_iter.first, "\":  ", 
	//				inner_iter.second.tok()->str(), ", ", 
	//				inner_iter.second.type(), "\n");
	//		}
	//	}
	//}
};


//std::ostream& operator << (std::ostream& os, const SymType& to_print);

//extern SymbolTable sym_tbl;

#endif		// symbol_table_class_hpp
