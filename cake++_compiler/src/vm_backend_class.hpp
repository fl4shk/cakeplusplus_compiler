#ifndef vm_backend_class_hpp
#define vm_backend_class_hpp

#include "backend_base_class.hpp"

class VmBackend : public BackendBase
{
private:		// variables
	VmCode __startup_vm_code;
	std::map<Function*, VmCode*> __func_to_code_map;

	//std::vector<VmCode*> __vm_code_pool;

public:		// functions
	VmBackend(std::vector<Function*>&& s_func_vec, 
		FunctionTable* s_func_tbl);
	virtual ~VmBackend();
	//void gen_code();
	std::ostream& osprint_code(std::ostream& os);
	
private:		// functions
	inline auto append_startup_code(VmRawInstrOp s_raw_op)
	{
		return mk_linked_vm_code(__startup_vm_code, s_raw_op);
	}
	inline auto append_func_code(VmRawInstrOp s_raw_op)
	{
		return mk_linked_vm_code(*__func_to_code_map.at(__curr_func),
			s_raw_op);
	}
	void __gen_startup_code();
	void __gen_one_code();
	std::ostream& __osprint_one_code(std::ostream& os, 
		VmCode& some_vm_code);
};

#endif		// vm_backend_class_hpp
