#include "backend_base_class.hpp"

BackendBase::BackendBase(std::vector<Function*>&& s_func_vec,
	FunctionTable* s_func_tbl)
	: __func_vec(std::move(s_func_vec)), __func_tbl(s_func_tbl)
{
}

BackendBase::~BackendBase()
{
}

void BackendBase::gen_code()
{
	// This is simple enough
	__gen_startup_code();


	for (auto iter : __func_vec)
	{
		__curr_func = iter;
		__gen_one_func_code();
	}
}
void BackendBase::handle_curr_func_ir_code_and_cleanup_lab_ident()
{
	++__curr_func->last_label_num();
	__cleanup_lab_ident = cstm_strdup(__func_tbl->get_label_name
		(__curr_func->last_label_num()));

	// Iterate directly through the IrCode of this function
	for (auto p=__curr_func->ir_code().next;
		p!=&__curr_func->ir_code();
		p=p->next)
	{
		set_curr_iop(p->iop());
		//switch (p->iop())
		switch (curr_iop())
		{
			// Store
			case IrInOp::St:
				handle_ir_code_st(p);
				break;

			// Return from subroutine
			case IrInOp::ReturnExpr:
				handle_ir_code_return_expr(p);
				break;
			case IrInOp::ReturnNothing:
				handle_ir_code_return_nothing(p);
				break;

			// Stop the program
			case IrInOp::Quit:
				handle_ir_code_quit(p);
				break;


			case IrInOp::Jump:
				handle_ir_code_jump(p);
				break;

			// Call form of code, ignoring return value
			case IrInOp::Call:
				handle_ir_code_call(p);
				break;

			case IrInOp::Syscall:
				handle_ir_code_syscall(p);
				break;
			case IrInOp::Label:
				handle_ir_code_label(p);
				break;

			default:
				printerr("BackendBase",
					"::handle_curr_func_ir_code_and_cleanup_lab_ident():  "
					"IrInOp Eek!\n");
				exit(1);
				break;
		}
	}
}
