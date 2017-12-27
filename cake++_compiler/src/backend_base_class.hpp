#ifndef backend_base_class_hpp
#define backend_base_class_hpp

//#include "scoped_table_base_class.hpp"
//#include "ir_code_stuff.hpp"
//#include "allocation_stuff.hpp"
#include "symbol_table_classes.hpp"


class VmCode;

// Base class for a backend
class BackendBase
{
protected:		// variables
	BackendCodeBase __startup_code;
	std::map<Function*, BackendCodeBase*> __func_to_code_start_map;
	BackendCodeBase* __curr_func_code = nullptr;


	// This is used so that functions get inserted in order
	std::vector<Function*> __func_vec;
	FunctionTable* __func_tbl;
	Function* __curr_func;

public:		// functions
	BackendBase(std::vector<Function*>&& s_func_vec, 
		FunctionTable* s_func_tbl);
	virtual ~BackendBase();
	void gen_code();
	std::ostream& osprint_code(std::ostream& os);


protected:		// functions
	virtual void __gen_startup_code() = 0;
	virtual void __gen_one_func_code() = 0;
	virtual std::ostream& __osprint_one_code(std::ostream& os,
		BackendCodeBase* some_code) = 0;

};

#endif		// backend_base_class_hpp
