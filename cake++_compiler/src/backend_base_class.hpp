#ifndef backend_base_class_hpp
#define backend_base_class_hpp

//#include "scoped_table_base_class.hpp"
//#include "ir_code_stuff.hpp"
//#include "allocation_stuff.hpp"
#include "symbol_table_classes.hpp"


// Base class for a backend
class BackendBase
{
protected:		// variables
	// This is used so that functions get inserted in order
	std::vector<Function*> __func_vec;
	FunctionTable* __func_tbl;
	Function* __curr_func;

public:		// functions
	BackendBase(std::vector<Function*>&& s_func_vec, 
		FunctionTable* s_func_tbl);
	virtual ~BackendBase();
	void gen_code();
	virtual std::ostream& osprint_code(std::ostream& os) = 0;

protected:		// functions
	virtual void __gen_startup_code() = 0;
	virtual void __gen_one_code() = 0;

};

#endif		// backend_base_class_hpp
