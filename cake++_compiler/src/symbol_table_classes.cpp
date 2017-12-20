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


SymbolTable::SymbolTable()
{
}

SymbolTable::~SymbolTable()
{
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

FunctionTable::FunctionTable()
{
}

FunctionTable::~FunctionTable()
{
}


