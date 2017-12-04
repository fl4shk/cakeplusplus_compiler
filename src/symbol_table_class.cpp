#include "symbol_table_class.hpp"


// The symbol table
SymbolTable sym_tbl;


void mkscope()
{
	sym_tbl.mkscope();
}

void rmscope()
{
	sym_tbl.rmscope();
}


SymbolTable::SymbolTable()
{
}

SymbolTable::~SymbolTable()
{
}

//std::ostream& operator << (std::ostream& os, const SymType& to_print)
//{
//	switch (to_print)
//	{
//		case SymType::Keyword:
//			os << "Keyword";
//			break;
//
//		case SymType::BuiltinTypename:
//			os << "BuiltinTypename";
//			break;
//
//		case SymType::VarName:
//			os << "VarName";
//			break;
//
//		case SymType::FuncName:
//			os << "FuncName";
//			break;
//
//		case SymType::StructName:
//			os << "StructName";
//			break;
//
//		default:
//			os << "Unknown";
//			break;
//	}
//
//	return os;
//}
