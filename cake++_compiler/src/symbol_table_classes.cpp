#include "symbol_table_classes.hpp"


//// The symbol table
//SymbolTable sym_tbl;


//void mkscope()
//{
//	sym_tbl.mkscope();
//}
//
//void rmscope()
//{
//	sym_tbl.rmscope();
//}

bool Symbol::is_unsgn_builtin() const
{
	return ((__var_type == BuiltinTypename::U8)
		|| (__var_type == BuiltinTypename::U16)
		|| (__var_type == BuiltinTypename::U32)
		|| (__var_type == BuiltinTypename::U64));
}

bool Symbol::is_sgn_builtin() const
{
	return ((__var_type == BuiltinTypename::S8)
		|| (__var_type == BuiltinTypename::S16)
		|| (__var_type == BuiltinTypename::S32)
		|| (__var_type == BuiltinTypename::S64));
}
s64 Symbol::builtin_type_size() const
{
	switch (var_type())
	{
		case BuiltinTypename::U64:
		case BuiltinTypename::S64:
			return sizeof(u64);
		case BuiltinTypename::U32:
		case BuiltinTypename::S32:
			return sizeof(u32);
		case BuiltinTypename::U16:
		case BuiltinTypename::S16:
			return sizeof(u16);
		case BuiltinTypename::U8:
		case BuiltinTypename::S8:
			return sizeof(u8);
		default:
			return -1;
	}
}
IrLdStSize Symbol::get_ldst_size() const
{
	switch (var_type())
	{
		case BuiltinTypename::U64:
		case BuiltinTypename::S64:
			return IrLdStSize::Sz64;
		case BuiltinTypename::U32:
		case BuiltinTypename::S32:
			return IrLdStSize::Sz32;
		case BuiltinTypename::U16:
		case BuiltinTypename::S16:
			return IrLdStSize::Sz16;
		case BuiltinTypename::U8:
		case BuiltinTypename::S8:
			return IrLdStSize::Sz8;
		default:
			return IrLdStSize::Unknown;
	}
}

SymbolTable::SymbolTable()
{
}

SymbolTable::~SymbolTable()
{
}

std::vector<Symbol*> Function::get_args() const
{
	std::vector<Symbol*> ret;

	std::map<size_t, Symbol*> pos_to_sym_map;

	//{
	//const auto& table = __sym_tbl.tree().children.front()->table.table();
	//for (const auto& iter : table)
	//{
	//	Symbol* sym = iter.second;

	//}
	//}

	return ret;
}

s64 Function::irntoi(IrCode* t) const
{
	s64 ret = -1;

	for (auto p=__ir_code.next; p!=&__ir_code; p=p->next)
	{
		++ret;

		if (p == t)
		{
			break;
		}
	}

	return ret;
}


