#ifndef vm_backend_class_hpp
#define vm_backend_class_hpp

#include "backend_base_class.hpp"

class VmBackend : public BackendBase
{
private:		// variables
	//VmCode __startup_vm_code;
	//std::map<Function*, VmCode*> __func_to_code_map;

	//VmCode* __curr_vm_code = nullptr;

	//VmCode* __node = nullptr;
	s64 __arg_space;
	s64 __ret_val_argx_offset;
	s64 __var_space;

public:		// functions
	VmBackend(std::vector<Function*>&& s_func_vec, 
		FunctionTable* s_func_tbl);
	virtual ~VmBackend();
	//std::ostream& osprint_code(std::ostream& os);
	

private:		// functions
	//inline auto append_startup_code(VmRawInstrOp s_raw_op)
	//{
	//	return mk_linked_vm_code(__startup_vm_code, s_raw_op);
	//}
	//inline auto append_func_code(VmRawInstrOp s_raw_op)
	//{
	//	return mk_linked_vm_code(*__func_to_code_map.at(__curr_func),
	//		s_raw_op);
	//}
	//inline auto append_code(VmRawInstrOp s_raw_op)
	//{
	//	return mk_linked_vm_code(*__curr_vm_code, s_raw_op);
	//}
	inline auto append_code(VmRawInstrOp s_raw_op)
	{
		auto ret = static_cast<VmCode*>
			(mk_linked_backend_base_code<VmCode>(__curr_func_code));
		ret->raw_op = s_raw_op;
		return ret;
	}
	void __gen_startup_code();
	void __gen_one_func_code();
	void __gen_from_ir_expr(IrExpr* expr);
	std::ostream& __osprint_one_code(std::ostream& os, 
		BackendCodeBase* some_code);


	// Cast that happens at runtime.
	BackendCodeBase* __gen_runtime_cast_to_64(IrMachineMode from_mm, 
		BackendCodeBase* p);

private:		// IR handler functions
	//BackendCodeBase* handle_ir_pure_expr(IrExpr* p);
	BackendCodeBase* __handle_ir_pure_expr_constant(IrExpr* p);
	BackendCodeBase* __handle_ir_pure_expr_binop(IrExpr* p);
	BackendCodeBase* __handle_ir_pure_expr_unop(IrExpr* p);
	BackendCodeBase* __handle_ir_pure_expr_len(IrExpr* p);
	BackendCodeBase* __handle_ir_pure_expr_sizeof(IrExpr* p);
	BackendCodeBase* __handle_ir_pure_expr_call_with_ret(IrExpr* p);
	BackendCodeBase* __handle_ir_pure_expr_address(IrExpr* p);
	BackendCodeBase* __handle_ir_pure_expr_ld(IrExpr* p);
	BackendCodeBase* __handle_ir_pure_expr_cast(IrExpr* p);

	BackendCodeBase* handle_ir_code_st(IrCode* p);
	BackendCodeBase* handle_ir_code_return_expr(IrCode* p);
	BackendCodeBase* handle_ir_code_return_nothing(IrCode* p);
	BackendCodeBase* handle_ir_code_quit(IrCode* p);
	BackendCodeBase* handle_ir_code_jump(IrCode* p);
	BackendCodeBase* handle_ir_code_call(IrCode* p);
	BackendCodeBase* handle_ir_code_syscall(IrCode* p);
	BackendCodeBase* handle_ir_code_label(IrCode* p);



private:		// code generation functions
	VmCode* mk_const(s64 s_imm_s64);
	VmCode* mk_const_func(Function* func_to_get_name_of);
	inline VmCode* mk_const_func(Ident s_func_ident)
	{
		return mk_const_func(__func_tbl->at(s_func_ident));
	}
	VmCode* mk_const_lab(Ident s_lab_ident);

	VmCode* mk_const_u32(u32 s_imm_u32);
	VmCode* mk_const_u32_func(Function* func_to_get_name_of);
	inline VmCode* mk_const_u32_func(Ident s_func_ident)
	{
		return mk_const_u32_func(__func_tbl->at(s_func_ident));
	}
	VmCode* mk_const_u32_lab(Ident s_lab_ident);

	VmCode* mk_const_s32(s32 s_imm_s32);
	VmCode* mk_const_s32_func(Function* func_to_get_name_of);
	inline VmCode* mk_const_s32_func(Ident s_func_ident)
	{
		return mk_const_s32_func(__func_tbl->at(s_func_ident));
	}
	VmCode* mk_const_s32_lab(Ident s_lab_ident);

	VmCode* mk_const_u16(u16 s_imm_u16);
	VmCode* mk_const_u16_func(Function* func_to_get_name_of);
	inline VmCode* mk_const_u16_func(Ident s_func_ident)
	{
		return mk_const_u16_func(__func_tbl->at(s_func_ident));
	}
	VmCode* mk_const_u16_lab(Ident s_lab_ident);

	VmCode* mk_const_s16(s16 s_imm_s16);
	VmCode* mk_const_s16_func(Function* func_to_get_name_of);
	inline VmCode* mk_const_s16_func(Ident s_func_ident)
	{
		return mk_const_s16_func(__func_tbl->at(s_func_ident));
	}
	VmCode* mk_const_s16_lab(Ident s_lab_ident);

	VmCode* mk_const_u8(u8 s_imm_u8);
	VmCode* mk_const_u8_func(Function* func_to_get_name_of);
	inline VmCode* mk_const_u8_func(Ident s_func_ident)
	{
		return mk_const_u8_func(__func_tbl->at(s_func_ident));
	}
	VmCode* mk_const_u8_lab(Ident s_lab_ident);

	VmCode* mk_const_s8(s8 s_imm_s8);
	VmCode* mk_const_s8_func(Function* func_to_get_name_of);
	inline VmCode* mk_const_s8_func(Ident s_func_ident)
	{
		return mk_const_s8_func(__func_tbl->at(s_func_ident));
	}
	VmCode* mk_const_s8_lab(Ident s_lab_ident);

	// These have different names from usual so as to help guard against
	// typos that would have lead to "arg" being used when "argx" was
	// intended.  Similar reasoning applies to "var" and "varx".
	VmCode* mk_arg_addr();
	VmCode* mk_indexed_arg_addr();
	VmCode* mk_var_addr();
	VmCode* mk_indexed_var_addr();

	VmCode* mk_get_pc();
	VmCode* mk_jump();

	VmCode* mk_beq_far(Ident s_lab_ident);
	VmCode* mk_bne_far(Ident s_lab_ident);
	VmCode* mk_beq_near(Ident s_lab_ident);
	VmCode* mk_bne_near(Ident s_lab_ident);

	VmCode* mk_call();
	VmCode* mk_ret();

	VmCode* mk_ld_basic();
	VmCode* mk_ld_u32();
	VmCode* mk_ld_s32();
	VmCode* mk_ld_u16();
	VmCode* mk_ld_s16();
	VmCode* mk_ld_u8();
	VmCode* mk_ld_s8();

	VmCode* mk_ldx_basic();
	VmCode* mk_ldx_u32();
	VmCode* mk_ldx_s32();
	VmCode* mk_ldx_u16();
	VmCode* mk_ldx_s16();
	VmCode* mk_ldx_u8();
	VmCode* mk_ldx_s8();


	VmCode* mk_st_basic();
	VmCode* mk_st_u32();
	VmCode* mk_st_s32();
	VmCode* mk_st_u16();
	VmCode* mk_st_s16();
	VmCode* mk_st_u8();
	VmCode* mk_st_s8();

	VmCode* mk_stx_basic();
	VmCode* mk_stx_u32();
	VmCode* mk_stx_s32();
	VmCode* mk_stx_u16();
	VmCode* mk_stx_s16();
	VmCode* mk_stx_u8();
	VmCode* mk_stx_s8();

	VmCode* mk_add_to_sp();

	VmCode* mk_add();
	VmCode* mk_sub();
	VmCode* mk_mul();
	VmCode* mk_udiv();
	VmCode* mk_sdiv();
	VmCode* mk_umod();
	VmCode* mk_smod();

	VmCode* mk_bit_and();
	VmCode* mk_bit_or();
	VmCode* mk_bit_xor();
	VmCode* mk_bit_lsl();
	VmCode* mk_bit_lsr();
	VmCode* mk_bit_asr();


	VmCode* mk_cmp_eq();
	VmCode* mk_cmp_ne();
	VmCode* mk_cmp_ult();
	VmCode* mk_cmp_slt();
	VmCode* mk_cmp_ugt();
	VmCode* mk_cmp_sgt();
	VmCode* mk_cmp_ule();
	VmCode* mk_cmp_sle();
	VmCode* mk_cmp_uge();
	VmCode* mk_cmp_sge();


	VmCode* mk_syscall();

	VmCode* mk_quit();

	VmCode* mk_fake_op_label(Ident s_lab_ident);
};

#endif		// vm_backend_class_hpp
