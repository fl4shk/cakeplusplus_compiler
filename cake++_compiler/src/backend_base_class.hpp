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

	IrInOp __curr_iop;
	//size_t __curr_ir_code_arg;

	Ident __cleanup_lab_ident = nullptr;

	bool __ir_code_is_st, __expr_is_st_address, __expr_is_ld_address, 
		__ir_code_st_var_is_arg;
	//Symbol* __ld_sym;
	std::stack<Symbol*> __ld_sym_stack;

public:		// functions
	BackendBase(std::vector<Function*>&& s_func_vec, 
		FunctionTable* s_func_tbl);
	virtual ~BackendBase();
	void gen_code();
	std::ostream& osprint_code(std::ostream& os);


protected:		// functions
	// Cast that happens at runtime.
	virtual BackendCodeBase* __gen_runtime_cast
		(IrMachineMode some_mm, BackendCodeBase* p, IrExpr* orig_expr,
		bool is_arg) = 0;
	virtual void __gen_startup_code() = 0;
	virtual void __gen_one_func_code() = 0;
	virtual std::ostream& __osprint_one_code(std::ostream& os,
		BackendCodeBase* some_code) = 0;

	inline void push_ld_sym(Symbol* to_push)
	{
		__ld_sym_stack.push(to_push);
	}
	inline auto pop_ld_sym()
	{
		auto ret = __ld_sym_stack.top();
		__ld_sym_stack.pop();
		return ret;
	}
	inline auto get_top_ld_sym()
	{
		return __ld_sym_stack.top();
	}
	
	gen_getter_and_setter_by_val(curr_iop);
	gen_getter_and_setter_by_val(ir_code_is_st);
	gen_getter_and_setter_by_val(expr_is_st_address);
	gen_getter_and_setter_by_val(expr_is_ld_address);
	gen_getter_and_setter_by_val(ir_code_st_var_is_arg);

protected:		// IR handler functions
	void handle_curr_func_ir_code_and_cleanup_lab_ident();
	BackendCodeBase* handle_ir_pure_expr(IrExpr* p);
	virtual BackendCodeBase* __handle_ir_pure_expr_constant(IrExpr* p) = 0;
	virtual BackendCodeBase* __handle_ir_pure_expr_binop(IrExpr* p) = 0;
	virtual BackendCodeBase* __handle_ir_pure_expr_unop(IrExpr* p) = 0;
	virtual BackendCodeBase* __handle_ir_pure_expr_len(IrExpr* p) = 0;
	virtual BackendCodeBase* __handle_ir_pure_expr_sizeof(IrExpr* p) = 0;
	virtual BackendCodeBase* 
		__handle_ir_pure_expr_call_with_ret(IrExpr* p) = 0;
	//virtual BackendCodeBase* __handle_ir_pure_expr_address(IrExpr* p) = 0;
	virtual BackendCodeBase* __handle_ir_pure_expr_arr_data_address
		(IrExpr* p) = 0;
	virtual BackendCodeBase* __handle_ir_pure_expr_real_address(IrExpr* p) 
		= 0;
	virtual BackendCodeBase* __handle_ir_pure_expr_ld(IrExpr* p) = 0;
	virtual BackendCodeBase* __handle_ir_pure_expr_cast(IrExpr* p) = 0;

	virtual BackendCodeBase* handle_ir_code_st(IrCode* p) = 0;
	virtual BackendCodeBase* handle_ir_code_return_expr(IrCode* p) = 0;
	virtual BackendCodeBase* handle_ir_code_return_nothing(IrCode* p) = 0;
	virtual BackendCodeBase* handle_ir_code_quit(IrCode* p) = 0;
	virtual BackendCodeBase* handle_ir_code_jump(IrCode* p) = 0;
	virtual BackendCodeBase* handle_ir_code_call(IrCode* p) = 0;
	virtual BackendCodeBase* handle_ir_code_syscall(IrCode* p) = 0;
	virtual BackendCodeBase* handle_ir_code_label(IrCode* p) = 0;

};

#endif		// backend_base_class_hpp
