#ifndef vm_backend_class_hpp
#define vm_backend_class_hpp

#include "backend_base_class.hpp"

class VmBackend : public BackendBase
{
private:		// variables
	VmCode __startup_vm_code;
	std::map<Function*, VmCode*> __func_to_code_map;

	VmCode* __curr_vm_code = nullptr;

	//std::vector<VmCode*> __vm_code_pool;

public:		// functions
	VmBackend(std::vector<Function*>&& s_func_vec, 
		FunctionTable* s_func_tbl);
	virtual ~VmBackend();
	std::ostream& osprint_code(std::ostream& os);
	

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
	inline auto append_code(VmRawInstrOp s_raw_op)
	{
		return mk_linked_vm_code(*__curr_vm_code, s_raw_op);
	}
	void __gen_startup_code();
	void __gen_one_code();
	std::ostream& __osprint_one_code(std::ostream& os, 
		VmCode& some_vm_code);

private:		// code generation functions
	VmCode* mk_const(u64 imm_s64);
	VmCode* mk_const(Function* func_to_get_name_of);
	VmCode* mk_const(Ident s_lab_ident);

	VmCode* mk_const_u32(u32 imm_u32);
	VmCode* mk_const_u32(Function* func_to_get_name_of);
	VmCode* mk_const_u32(Ident s_lab_ident);

	VmCode* mk_const_s32(s32 imm_s32);
	VmCode* mk_const_s32(Function* func_to_get_name_of);
	VmCode* mk_const_s32(Ident s_lab_ident);

	VmCode* mk_const_u16(u16 imm_u16);
	VmCode* mk_const_u16(Function* func_to_get_name_of);
	VmCode* mk_const_u16(Ident s_lab_ident);

	VmCode* mk_const_s16(s16 imm_s16);
	VmCode* mk_const_s16(Function* func_to_get_name_of);
	VmCode* mk_const_s16(Ident s_lab_ident);

	VmCode* mk_const_u8(u8 imm_u8);
	VmCode* mk_const_u8(Function* func_to_get_name_of);
	VmCode* mk_const_u8(Ident s_lab_ident);

	VmCode* mk_const_s8(s8 imm_s8);
	VmCode* mk_const_s8(Function* func_to_get_name_of);
	VmCode* mk_const_s8(Ident s_lab_ident);

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
};

#endif		// vm_backend_class_hpp
