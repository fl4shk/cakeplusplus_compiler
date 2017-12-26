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
	__gen_startup_code();


	for (auto iter : __func_vec)
	{
		__curr_func = iter;
		__gen_one_code();
	}
}
