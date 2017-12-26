#include "symbol_table_classes.hpp"
#include "allocation_stuff.hpp"


std::ostream& operator << (std::ostream& os, 
	BuiltinTypename some_builtin_typename)
{
	switch (some_builtin_typename)
	{
		case BuiltinTypename::Blank:
			return osprintout(os, "Blank");

		case BuiltinTypename::U64:
			return osprintout(os, "u64");
		case BuiltinTypename::S64:
			return osprintout(os, "s64");

		case BuiltinTypename::U32:
			return osprintout(os, "u32");
		case BuiltinTypename::S32:
			return osprintout(os, "s32");

		case BuiltinTypename::U16:
			return osprintout(os, "u16");
		case BuiltinTypename::S16:
			return osprintout(os, "s16");

		case BuiltinTypename::U8:
			return osprintout(os, "u8");
		case BuiltinTypename::S8:
			return osprintout(os, "s8");

		default:
			printerr("BuiltinTypename osprintout stuff:  Eek!\n");
			exit(1);
	}

	return os;
}

bool Var::is_unsgn_builtin() const
{
	return ((__type == BuiltinTypename::U8)
		|| (__type == BuiltinTypename::U16)
		|| (__type == BuiltinTypename::U32)
		|| (__type == BuiltinTypename::U64));
}

bool Var::is_sgn_builtin() const
{
	return ((__type == BuiltinTypename::S8)
		|| (__type == BuiltinTypename::S16)
		|| (__type == BuiltinTypename::S32)
		|| (__type == BuiltinTypename::S64));
}
s64 Var::builtin_type_size() const
{
	switch (type())
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
//IrLdStSize Symbol::get_ldst_size() const
//{
//	switch (var_type())
//	{
//		case BuiltinTypename::U64:
//		case BuiltinTypename::S64:
//			return IrLdStSize::Sz64;
//		case BuiltinTypename::U32:
//		case BuiltinTypename::S32:
//			return IrLdStSize::Sz32;
//		case BuiltinTypename::U16:
//		case BuiltinTypename::S16:
//			return IrLdStSize::Sz16;
//		case BuiltinTypename::U8:
//		case BuiltinTypename::S8:
//			return IrLdStSize::Sz8;
//		default:
//			return IrLdStSize::Unknown;
//	}
//}
Ident Symbol::name() const
{
	switch (type())
	{
		case SymType::ScalarVarName:
		case SymType::ArrayVarName:
			return var()->name();
			break;

		case SymType::FuncName:
			return func()->name();
			break;

		//case SymType::ClassName:
		//	cls()->set_name(n_name);
		//	break;
		
		default:
			printerr("Symbol::name():  Eek!\n");
			exit(1);
			break;
	}
}
void Symbol::set_name(Ident n_name)
{
	switch (type())
	{
		case SymType::ScalarVarName:
		case SymType::ArrayVarName:
			var()->set_name(n_name);
			break;

		case SymType::FuncName:
			func()->set_name(n_name);
			break;

		//case SymType::ClassName:
		//	cls()->set_name(n_name);
		//	break;
		
		default:
			printerr("Symbol::set_name():  Eek!\n");
			exit(1);
			break;
	}
}

SymbolTable::SymbolTable()
{
}

SymbolTable::~SymbolTable()
{
}

std::vector<Symbol*> Function::get_args() const
//std::vector<Symbol*> Function::get_args(SymbolTable& some_sym_tbl) const
{
	std::vector<Symbol*> ret;

	std::map<size_t, Symbol*> arg_pos_to_sym_map;

	size_t num_args = 0;

	{
	//const auto& table = __sym_tbl.tree().children.front()->table.table();
	//const auto& table = __syms->table;
	//const auto& table = __scope_node->children.front()->table.table();
	const auto& table = get_args_scope_node()->table.table();
	
	for (const auto& iter : table)
	{
		auto sym = iter.second;

		if (arg_pos_to_sym_map.count(sym->var()->arg_offset()) != 0)
		{
			printerr("Function::get_args():  Eek!\n");
			exit(1);
		}

		arg_pos_to_sym_map[sym->var()->arg_offset()] = sym;

		//// Find the highest argument offset
		//if (num_args < sym->var()->arg_offset())
		//{
		//	num_args = sym->var()->arg_offset();
		//}
		++num_args;
	}

	}

	//++num_args;

	// Increment because no argument symbol keeps track of how many
	// arguments this function accepts

	for (size_t i=0; i<num_args; ++i)
	{
		ret.push_back(arg_pos_to_sym_map.at(i));
	}

	return ret;
}

//Symbol* Function::get_one_arg(size_t some_arg_offset) const
//{
//	const auto& table = __sym_tbl.tree().children.front()->table.table();
//
//	for (const auto& iter : table)
//	{
//		if (iter.second->arg_offset() == some_arg_offset)
//		{
//			return iter.second;
//		}
//	}
//
//	return nullptr;
//}

//s64 Function::offset_of_vm_code(VmCode* v) const
//{
//	s64 offset = 0;
//
//	for (auto p=__vm_code.next; p!=&__vm_code; p=p->next)
//	{
//		if (p == v)
//		{
//			return offset;
//		}
//
//		offset += p->size;
//	}
//	return -1;
//}





FunctionTable::FunctionTable()
{
}

FunctionTable::~FunctionTable()
{
}

std::string FunctionTable::get_label_name(s64 some_lab_num) const
{
	std::string ret = sconcat(some_lab_num);

	// Don't have any labels with the same identifier as any functions
	do
	{
		ret = sconcat("_", ret);
	} while (contains(cstm_strdup(ret)));

	return ret;
}
