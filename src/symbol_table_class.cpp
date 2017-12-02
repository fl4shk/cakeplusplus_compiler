#include "symbol_table_class.hpp"
#include <string.h>

SymbolTable sym_tbl;

SymbolTable::SymbolTable()
{
}

SymbolTable::~SymbolTable()
{
}

void SymbolTable::make_var(const std::string& some_var_name)
{
	if (sym_tbl.__table.count(some_var_name) == 0)
	{
		sym_tbl.__table[some_var_name] = Symbol();
		sym_tbl.__table.at(some_var_name).name = some_var_name;
		sym_tbl.__table.at(some_var_name).val = 0;
	}
}

s32 get_var_val(const std::string& some_var_name)
{
	printout("Grabbing ", some_var_name, "'s value of ");
	const auto ret = sym_tbl.__table.at(some_var_name).val;
	printout(ret, "\n");
	return ret;
}
void set_var_val(const std::string& some_var_name, s32 n_val)
{
	printout("Setting ", some_var_name, " to ", n_val, "\n");
	sym_tbl.__table.at(some_var_name).val = n_val;
}
const std::string& get_curr_var_name()
{
	return sym_tbl.curr_var_name;
}

extern "C"
{
const char* set_curr_var_name(char* some_var_name)
{
	//printout("set_curr_var_name(\"", some_var_name, "\")\n");
	//sym_tbl.curr_var_name = strdup(some_var_name);

	sym_tbl.curr_var_name = "";

	for (size_t i=0; i<strlen(some_var_name); ++i)
	{
		sym_tbl.curr_var_name += some_var_name[i];
	}

	return sym_tbl.curr_var_name.c_str();
}
void make_curr_var()
{
	//printout("make_curr_var()\n");
	sym_tbl.make_var(get_curr_var_name());
}
}
