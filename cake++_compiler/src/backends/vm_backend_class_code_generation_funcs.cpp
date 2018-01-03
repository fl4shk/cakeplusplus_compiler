#include "vm_backend_class.hpp"

//VmCode* VmBackend::mk_const(s64 s_imm_s64)
//{
//	auto ret = append_code(VmRawInstrOp::constant_64);
//	ret->imm_s64 = s_imm_s64;
//	return ret;
//}
//VmCode* VmBackend::mk_const_func(Function* func_to_get_name_of)
//{
//	auto ret = append_code(VmRawInstrOp::constant_64);
//	ret->func_ident = func_to_get_name_of->name();
//	return ret;
//}
//VmCode* VmBackend::mk_const_lab(Ident s_lab_ident)
//{
//	auto ret = append_code(VmRawInstrOp::constant_64);
//	ret->lab_ident = s_lab_ident;
//	return ret;
//}
//
//VmCode* VmBackend::mk_const_u32(u32 s_imm_u32)
//{
//	auto ret = append_code(VmRawInstrOp::constant_u32);
//	ret->imm_u32 = s_imm_u32;
//	return ret;
//}
//VmCode* VmBackend::mk_const_u32_func(Function* func_to_get_name_of)
//{
//	auto ret = append_code(VmRawInstrOp::constant_u32);
//	ret->func_ident = func_to_get_name_of->name();
//	return ret;
//}
//VmCode* VmBackend::mk_const_u32_lab(Ident s_lab_ident)
//{
//	auto ret = append_code(VmRawInstrOp::constant_u32);
//	ret->lab_ident = s_lab_ident;
//	return ret;
//}
//
//VmCode* VmBackend::mk_const_s32(s32 s_imm_s32)
//{
//	auto ret = append_code(VmRawInstrOp::constant_s32);
//	ret->imm_s32 = s_imm_s32;
//	return ret;
//}
//VmCode* VmBackend::mk_const_s32_func(Function* func_to_get_name_of)
//{
//	auto ret = append_code(VmRawInstrOp::constant_s32);
//	ret->func_ident = func_to_get_name_of->name();
//	return ret;
//}
//VmCode* VmBackend::mk_const_s32_lab(Ident s_lab_ident)
//{
//	auto ret = append_code(VmRawInstrOp::constant_s32);
//	ret->lab_ident = s_lab_ident;
//	return ret;
//}
//
//VmCode* VmBackend::mk_const_u16(u16 s_imm_u16)
//{
//	auto ret = append_code(VmRawInstrOp::constant_u16);
//	ret->imm_u16 = s_imm_u16;
//	return ret;
//}
//VmCode* VmBackend::mk_const_u16_func(Function* func_to_get_name_of)
//{
//	auto ret = append_code(VmRawInstrOp::constant_u16);
//	ret->func_ident = func_to_get_name_of->name();
//	return ret;
//}
//VmCode* VmBackend::mk_const_u16_lab(Ident s_lab_ident)
//{
//	auto ret = append_code(VmRawInstrOp::constant_u16);
//	ret->lab_ident = s_lab_ident;
//	return ret;
//}
//
//VmCode* VmBackend::mk_const_s16(s16 s_imm_s16)
//{
//	auto ret = append_code(VmRawInstrOp::constant_s16);
//	ret->imm_s16 = s_imm_s16;
//	return ret;
//}
//VmCode* VmBackend::mk_const_s16_func(Function* func_to_get_name_of)
//{
//	auto ret = append_code(VmRawInstrOp::constant_s16);
//	ret->func_ident = func_to_get_name_of->name();
//	return ret;
//}
//VmCode* VmBackend::mk_const_s16_lab(Ident s_lab_ident)
//{
//	auto ret = append_code(VmRawInstrOp::constant_s16);
//	ret->lab_ident = s_lab_ident;
//	return ret;
//}
//
//VmCode* VmBackend::mk_const_u8(u8 s_imm_u8)
//{
//	auto ret = append_code(VmRawInstrOp::constant_u8);
//	ret->imm_u8 = s_imm_u8;
//	return ret;
//}
//VmCode* VmBackend::mk_const_u8_func(Function* func_to_get_name_of)
//{
//	auto ret = append_code(VmRawInstrOp::constant_u8);
//	ret->func_ident = func_to_get_name_of->name();
//	return ret;
//}
//VmCode* VmBackend::mk_const_u8_lab(Ident s_lab_ident)
//{
//	auto ret = append_code(VmRawInstrOp::constant_u8);
//	ret->lab_ident = s_lab_ident;
//	return ret;
//}
//
//VmCode* VmBackend::mk_const_s8(s8 s_imm_s8)
//{
//	auto ret = append_code(VmRawInstrOp::constant_s8);
//	ret->imm_s8 = s_imm_s8;
//	return ret;
//}
//VmCode* VmBackend::mk_const_s8_func(Function* func_to_get_name_of)
//{
//	auto ret = append_code(VmRawInstrOp::constant_s8);
//	ret->func_ident = func_to_get_name_of->name();
//	return ret;
//}
//VmCode* VmBackend::mk_const_s8_lab(Ident s_lab_ident)
//{
//	auto ret = append_code(VmRawInstrOp::constant_s8);
//	ret->lab_ident = s_lab_ident;
//	return ret;
//}
//
//VmCode* VmBackend::mk_arg_addr()
//{
//	return append_code(VmRawInstrOp::arg);
//}
//VmCode* VmBackend::mk_indexed_arg_addr()
//{
//	return append_code(VmRawInstrOp::argx);
//}
//VmCode* VmBackend::mk_var_addr()
//{
//	return append_code(VmRawInstrOp::var);
//}
//VmCode* VmBackend::mk_indexed_var_addr()
//{
//	return append_code(VmRawInstrOp::varx);
//}
//
//VmCode* VmBackend::mk_get_pc()
//{
//	return append_code(VmRawInstrOp::get_pc);
//}
//VmCode* VmBackend::mk_jump()
//{
//	return append_code(VmRawInstrOp::jump);
//}
//
//VmCode* VmBackend::mk_beq_far(Ident s_lab_ident)
//{
//	auto ret = append_code(VmRawInstrOp::beq);
//	ret->lab_ident = s_lab_ident;
//	return ret;
//}
//VmCode* VmBackend::mk_bne_far(Ident s_lab_ident)
//{
//	auto ret = append_code(VmRawInstrOp::bne);
//	ret->lab_ident = s_lab_ident;
//	return ret;
//}
//VmCode* VmBackend::mk_beq_near(Ident s_lab_ident)
//{
//	auto ret = append_code(VmRawInstrOp::beq_near);
//	ret->lab_ident = s_lab_ident;
//	return ret;
//}
//VmCode* VmBackend::mk_bne_near(Ident s_lab_ident)
//{
//	auto ret = append_code(VmRawInstrOp::bne_near);
//	ret->lab_ident = s_lab_ident;
//	return ret;
//}
//
//VmCode* VmBackend::mk_call()
//{
//	return append_code(VmRawInstrOp::call);
//}
//VmCode* VmBackend::mk_ret()
//{
//	return append_code(VmRawInstrOp::ret);
//}
//
//VmCode* VmBackend::mk_ld_basic()
//{
//	return append_code(VmRawInstrOp::ld_basic);
//}
//VmCode* VmBackend::mk_ld_u32()
//{
//	return append_code(VmRawInstrOp::ld_u32);
//}
//VmCode* VmBackend::mk_ld_s32()
//{
//	return append_code(VmRawInstrOp::ld_s32);
//}
//VmCode* VmBackend::mk_ld_u16()
//{
//	return append_code(VmRawInstrOp::ld_u16);
//}
//VmCode* VmBackend::mk_ld_s16()
//{
//	return append_code(VmRawInstrOp::ld_s16);
//}
//VmCode* VmBackend::mk_ld_u8()
//{
//	return append_code(VmRawInstrOp::ld_u8);
//}
//VmCode* VmBackend::mk_ld_s8()
//{
//	return append_code(VmRawInstrOp::ld_s8);
//}
//
//VmCode* VmBackend::mk_ldx_basic()
//{
//	return append_code(VmRawInstrOp::ldx_basic);
//}
//VmCode* VmBackend::mk_ldx_u32()
//{
//	return append_code(VmRawInstrOp::ldx_u32);
//}
//VmCode* VmBackend::mk_ldx_s32()
//{
//	return append_code(VmRawInstrOp::ldx_s32);
//}
//VmCode* VmBackend::mk_ldx_u16()
//{
//	return append_code(VmRawInstrOp::ldx_u16);
//}
//VmCode* VmBackend::mk_ldx_s16()
//{
//	return append_code(VmRawInstrOp::ldx_s16);
//}
//VmCode* VmBackend::mk_ldx_u8()
//{
//	return append_code(VmRawInstrOp::ldx_u8);
//}
//VmCode* VmBackend::mk_ldx_s8()
//{
//	return append_code(VmRawInstrOp::ldx_s8);
//}
//
//
//VmCode* VmBackend::mk_st_basic()
//{
//	return append_code(VmRawInstrOp::st_basic);
//}
//VmCode* VmBackend::mk_st_u32()
//{
//	return append_code(VmRawInstrOp::st_u32);
//}
//VmCode* VmBackend::mk_st_s32()
//{
//	return append_code(VmRawInstrOp::st_s32);
//}
//VmCode* VmBackend::mk_st_u16()
//{
//	return append_code(VmRawInstrOp::st_u16);
//}
//VmCode* VmBackend::mk_st_s16()
//{
//	return append_code(VmRawInstrOp::st_s16);
//}
//VmCode* VmBackend::mk_st_u8()
//{
//	return append_code(VmRawInstrOp::st_u8);
//}
//VmCode* VmBackend::mk_st_s8()
//{
//	return append_code(VmRawInstrOp::st_s8);
//}
//
//VmCode* VmBackend::mk_stx_basic()
//{
//	return append_code(VmRawInstrOp::stx_basic);
//}
//VmCode* VmBackend::mk_stx_u32()
//{
//	return append_code(VmRawInstrOp::stx_u32);
//}
//VmCode* VmBackend::mk_stx_s32()
//{
//	return append_code(VmRawInstrOp::stx_s32);
//}
//VmCode* VmBackend::mk_stx_u16()
//{
//	return append_code(VmRawInstrOp::stx_u16);
//}
//VmCode* VmBackend::mk_stx_s16()
//{
//	return append_code(VmRawInstrOp::stx_s16);
//}
//VmCode* VmBackend::mk_stx_u8()
//{
//	return append_code(VmRawInstrOp::stx_u8);
//}
//VmCode* VmBackend::mk_stx_s8()
//{
//	return append_code(VmRawInstrOp::stx_s8);
//}
//
//VmCode* VmBackend::mk_add_to_sp()
//{
//	return append_code(VmRawInstrOp::add_to_sp);
//}
//
//VmCode* VmBackend::mk_add()
//{
//	return append_code(VmRawInstrOp::add);
//}
//VmCode* VmBackend::mk_sub()
//{
//	return append_code(VmRawInstrOp::sub);
//}
//VmCode* VmBackend::mk_mul()
//{
//	return append_code(VmRawInstrOp::mul);
//}
//VmCode* VmBackend::mk_udiv()
//{
//	return append_code(VmRawInstrOp::udiv);
//}
//VmCode* VmBackend::mk_sdiv()
//{
//	return append_code(VmRawInstrOp::sdiv);
//}
//VmCode* VmBackend::mk_umod()
//{
//	return append_code(VmRawInstrOp::umod);
//}
//VmCode* VmBackend::mk_smod()
//{
//	return append_code(VmRawInstrOp::smod);
//}
//
//VmCode* VmBackend::mk_bit_and()
//{
//	return append_code(VmRawInstrOp::bit_and);
//}
//VmCode* VmBackend::mk_bit_or()
//{
//	return append_code(VmRawInstrOp::bit_or);
//}
//VmCode* VmBackend::mk_bit_xor()
//{
//	return append_code(VmRawInstrOp::bit_xor);
//}
//VmCode* VmBackend::mk_bit_lsl()
//{
//	return append_code(VmRawInstrOp::bit_lsl);
//}
//VmCode* VmBackend::mk_bit_lsr()
//{
//	return append_code(VmRawInstrOp::bit_lsr);
//}
//VmCode* VmBackend::mk_bit_asr()
//{
//	return append_code(VmRawInstrOp::bit_asr);
//}
//
//
//VmCode* VmBackend::mk_cmp_eq()
//{
//	return append_code(VmRawInstrOp::cmp_eq);
//}
//VmCode* VmBackend::mk_cmp_ne()
//{
//	return append_code(VmRawInstrOp::cmp_ne);
//}
//VmCode* VmBackend::mk_cmp_ult()
//{
//	return append_code(VmRawInstrOp::cmp_ult);
//}
//VmCode* VmBackend::mk_cmp_slt()
//{
//	return append_code(VmRawInstrOp::cmp_slt);
//}
//VmCode* VmBackend::mk_cmp_ugt()
//{
//	return append_code(VmRawInstrOp::cmp_ugt);
//}
//VmCode* VmBackend::mk_cmp_sgt()
//{
//	return append_code(VmRawInstrOp::cmp_sgt);
//}
//VmCode* VmBackend::mk_cmp_ule()
//{
//	return append_code(VmRawInstrOp::cmp_ule);
//}
//VmCode* VmBackend::mk_cmp_sle()
//{
//	return append_code(VmRawInstrOp::cmp_sle);
//}
//VmCode* VmBackend::mk_cmp_uge()
//{
//	return append_code(VmRawInstrOp::cmp_uge);
//}
//VmCode* VmBackend::mk_cmp_sge()
//{
//	return append_code(VmRawInstrOp::cmp_sge);
//}
//
//
//VmCode* VmBackend::mk_syscall()
//{
//	return append_code(VmRawInstrOp::syscall);
//}
//
//VmCode* VmBackend::mk_quit()
//{
//	return append_code(VmRawInstrOp::quit);
//}
//
//VmCode* VmBackend::mk_fake_op_label(Ident s_lab_ident)
//{
//	auto ret = append_code(VmRawInstrOp::fake_op_label);
//	ret->lab_ident = s_lab_ident;
//	return ret;
//}
