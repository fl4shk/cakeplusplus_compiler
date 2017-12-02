#ifndef symbol_table_class_hpp
#define symbol_table_class_hpp

#include "misc_includes.hpp"
#include "symbol_table_extern_funcs.hpp"

class SymbolTable
{
public:		// classes
	class Symbol
	{
	public:		// variables
		std::string name;
		s32 val;
	};

private:		// variables
	std::map<std::string, Symbol> __table;

public:		// variables
	std::string curr_var_name;

public:		// functions
	SymbolTable();
	virtual ~SymbolTable();

	void make_var(const std::string& some_var_name);

	friend s32 get_var_val(const std::string& some_var_name);
	friend void set_var_val(const std::string& some_var_name, s32 n_val);
	friend const std::string& get_curr_var_name();
};

#endif		// symbol_table_class_hpp
