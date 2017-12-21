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

std::ostream& operator << (std::ostream& os, 
	BuiltinTypename some_builtin_type)
{
	switch (some_builtin_type)
	{
		case BuiltinTypename::Blank:
			return osprintout(os, "Blank");
		case BuiltinTypename::U8:
			return osprintout(os, "u8");
		case BuiltinTypename::U16:
			return osprintout(os, "u16");
		case BuiltinTypename::U32:
			return osprintout(os, "u32");
		case BuiltinTypename::U64:
			return osprintout(os, "u64");
		case BuiltinTypename::S8:
			return osprintout(os, "s8");
		case BuiltinTypename::S16:
			return osprintout(os, "s16");
		case BuiltinTypename::S32:
			return osprintout(os, "s32");
		case BuiltinTypename::S64:
			return osprintout(os, "s64");
		default:
			printerr("BuiltinTypename osprintout stuff:  Eek!\n");
			exit(1);
	}

	return os;
}

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

	std::map<size_t, Symbol*> arg_pos_to_sym_map;

	size_t num_args = 0;

	{
	const auto& table = __sym_tbl.tree().children.front()->table.table();
	for (const auto& iter : table)
	{
		auto sym = iter.second;

		if (arg_pos_to_sym_map.count(sym->arg_offset()) != 0)
		{
			printerr("Function::get_args():  Eek!\n");
			exit(1);
		}

		arg_pos_to_sym_map[sym->arg_offset()] = sym;

		// Find the highest argument offset
		if (num_args < sym->arg_offset())
		{
			num_args = sym->arg_offset();
		}
	}
	}

	// Increment because no argument symbol keeps track of how many
	// arguments this function accepts
	++num_args;

	for (size_t i=0; i<num_args; ++i)
	{
		ret.push_back(arg_pos_to_sym_map.at(i));
	}

	return ret;
}

Symbol* Function::get_one_arg(size_t some_arg_offset) const
{
	const auto& table = __sym_tbl.tree().children.front()->table.table();

	for (const auto& iter : table)
	{
		if (iter.second->arg_offset() == some_arg_offset)
		{
			return iter.second;
		}
	}

	return nullptr;
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


