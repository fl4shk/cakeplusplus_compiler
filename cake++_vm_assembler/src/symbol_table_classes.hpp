#ifndef symbol_table_classes_hpp
#define symbol_table_classes_hpp

#include "misc_includes.hpp"

#include "scoped_ident_table_class.hpp"


class Symbol
{
private:		// variables
	Ident __name;


public:		// functions
	inline Symbol()
	{
	}
	inline Symbol(Ident s_name)
		: __name(s_name)
	{
	}
	inline Symbol(const Symbol& to_copy) = default;
	inline Symbol(Symbol&& to_move) = default;

	inline Symbol& operator = (const Symbol& to_copy) = default;
	inline Symbol& operator = (Symbol&& to_move) = default;

	gen_getter_and_setter_by_con_ref(name);
	gen_setter_by_rval_ref(name);
};


class SymbolTable : public ScopedIdentTable<Symbol>
{
public:		// functions
	SymbolTable();
	virtual ~SymbolTable();
};




#endif		// symbol_table_classes_hpp
