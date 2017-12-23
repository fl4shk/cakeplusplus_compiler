#include "ir_code_stuff.hpp"

IrExpr::IrExpr(IrExpr* s_parent)
	: parent(s_parent)
{
}
IrExpr::~IrExpr()
{
}




IrCode::IrCode()
{
}
IrCode::IrCode(IrInOp s_iop)
	: __iop(s_iop)
{
	__iop = s_iop;
}
IrCode::~IrCode()
{
}
