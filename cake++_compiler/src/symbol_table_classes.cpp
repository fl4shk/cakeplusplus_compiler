#include "symbol_table_classes.hpp"
#include "allocation_stuff.hpp"

s64 get_builtin_typename_size(BuiltinTypename some_builtin_typename)
{
	//switch (type())
	switch (some_builtin_typename)
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




std::vector<Symbol*> Function::get_local_vars() const
{
	std::vector<Symbol*> ret;

	std::map<size_t, Symbol*> local_var_pos_to_sym_map;

	size_t num_local_vars = 0;


	// Grab all the local variable tables.
	auto&& local_var_tables = get_args_scope_node()
		->get_all_children_tables();

	// For now, this does not allow re-use of already-allocated memory when
	// what it was allocated for goes out of scope.
	// 
	// This is really only an issue because the "var" and "varx"
	// instructions use the same base address unless another function call
	// is performed.
	// 
	// It is technically possible to, at compile time, 
	// keep track of how far along one is in the stack, so perhaps that's
	// what will be done.
	for (auto outer_iter : local_var_tables)
	{
		for (auto iter : *outer_iter)
		{
			auto sym = iter.second;
				 sym->var()->local_var_offset();

			if (local_var_pos_to_sym_map.count
				(sym->var()->local_var_offset()) != 0)
			{
				printerr("Function::get_local_vars():  Eek!\n");
				exit(1);
			}

			local_var_pos_to_sym_map[sym->var()->local_var_offset()] = sym;
			++num_local_vars;

			//printout(*sym->name(), "\n");
		}
	}
	//printout("\n\n");


	//printout(*name(), ":  \n");
	//printout("{\n");
	for (size_t i=0; i<num_local_vars; ++i)
	{
		auto temp = local_var_pos_to_sym_map.at(i);

		//printout("\t", *temp->name(), "\n");


		ret.push_back(temp);
	}
	//printout("}\n");

	//printout("\n\n");

	return ret;
}


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
