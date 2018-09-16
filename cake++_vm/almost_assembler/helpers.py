#! /usr/bin/env python3

from enum import IntEnum, auto


class AlmostAssembler:
	def __init__(self):
		self.__f = open("input.bin", mode="wb")
		self.__pc = 0

	def pc(self):
		return self.__pc

	def __write_bytes(self, some_list):
		ret = self.__pc

		to_write = bytes(some_list)
		self.__pc += len(to_write)
		self.__f.write(to_write)

		return ret


	def __write_8_bit(self, some_int):
		self.__write_bytes([some_int & 0xff])

	def __write_16_bit(self, some_int):
		self.__write_8_bit(some_int >> 8)
		self.__write_8_bit(some_int)

	def __write_32_bit(self, some_int):
		self.__write_16_bit(some_int >> 16)
		self.__write_16_bit(some_int)

	def __write_64_bit(self, some_int):
		self.__write_32_bit(some_int >> 32)
		self.__write_32_bit(some_int)

	def __encode_instr_header(self, group, oper):
		ret = self.__write_8_bit(group)
		self.__write_8_bit(oper)
		return ret

	def __encode_grp_0_instr(self, oper):
		return self.__encode_instr_header(0, oper)

	def __encode_grp_1_instr(self, oper, simm16):
		ret = self.__encode_instr_header(1, oper)
		self = self.__write_16_bit(simm16)
		return ret

	def __encode_grp_2_instr(self, oper, immediate):
		ret = self.__encode_instr_header(2, oper)

		if ((oper == self.InstrGrp2Oper.Constu8)
			or (oper == self.InstrGrp2Oper.Consts8)):
			self.__write_8_bit(immediate)
		elif ((oper == self.InstrGrp2Oper.Constu16)
			or (oper == self.InstrGrp2Oper.Consts16)):
			self.__write_16_bit(immediate)
		elif ((oper == self.InstrGrp2Oper.Constu32)
			or (oper == self.InstrGrp2Oper.Consts32)):
			self.__write_32_bit(immediate)
		elif (oper == self.InstrGrp2Oper.Const64):
			self.__write_64_bit(immediate)

		return ret

	def __encode_grp_3_instr(self, oper):
		return self.__encode_instr_header(3, oper)
	def __encode_grp_4_instr(self, oper):
		return self.__encode_instr_header(4, oper)

	def enc_add(self):
		return self.__encode_grp_0_instr(self.InstrGrp0Oper.Add)
	def enc_sub(self):
		return self.__encode_grp_0_instr(self.InstrGrp0Oper.Sub)
	def enc_mul(self):
		return self.__encode_grp_0_instr(self.InstrGrp0Oper.Mul)
	def enc_udiv(self):
		return self.__encode_grp_0_instr(self.InstrGrp0Oper.Udiv)
	def enc_sdiv(self):
		return self.__encode_grp_0_instr(self.InstrGrp0Oper.Sdiv)
	def enc_umod(self):
		return self.__encode_grp_0_instr(self.InstrGrp0Oper.Umod)
	def enc_smod(self):
		return self.__encode_grp_0_instr(self.InstrGrp0Oper.Smod)
	def enc_uslt(self):
		return self.__encode_grp_0_instr(self.InstrGrp0Oper.Uslt)
	def enc_sslt(self):
		return self.__encode_grp_0_instr(self.InstrGrp0Oper.Sslt)
	def enc_and(self):
		return self.__encode_grp_0_instr(self.InstrGrp0Oper.And)
	def enc_or(self):
		return self.__encode_grp_0_instr(self.InstrGrp0Oper.Or)
	def enc_xor(self):
		return self.__encode_grp_0_instr(self.InstrGrp0Oper.Xor)
	def enc_lsl(self):
		return self.__encode_grp_0_instr(self.InstrGrp0Oper.Lsl)
	def enc_lsr(self):
		return self.__encode_grp_0_instr(self.InstrGrp0Oper.Lsr)
	def enc_asr(self):
		return self.__encode_grp_0_instr(self.InstrGrp0Oper.Asr)
	def enc_ldux8(self):
		return self.__encode_grp_0_instr(self.InstrGrp0Oper.Ldux8)
	def enc_ldsx8(self):
		return self.__encode_grp_0_instr(self.InstrGrp0Oper.Ldsx8)
	def enc_ldux16(self):
		return self.__encode_grp_0_instr(self.InstrGrp0Oper.Ldux16)
	def enc_ldsx16(self):
		return self.__encode_grp_0_instr(self.InstrGrp0Oper.Ldsx16)
	def enc_ldux32(self):
		return self.__encode_grp_0_instr(self.InstrGrp0Oper.Ldux32)
	def enc_ldsx32(self):
		return self.__encode_grp_0_instr(self.InstrGrp0Oper.Ldsx32)
	def enc_ldx64(self):
		return self.__encode_grp_0_instr(self.InstrGrp0Oper.Ldx64)
	def enc_stx8(self):
		return self.__encode_grp_0_instr(self.InstrGrp0Oper.Stx8)
	def enc_stx16(self):
		return self.__encode_grp_0_instr(self.InstrGrp0Oper.Stx16)
	def enc_stx32(self):
		return self.__encode_grp_0_instr(self.InstrGrp0Oper.Stx32)
	def enc_stx64(self):
		return self.__encode_grp_0_instr(self.InstrGrp0Oper.Stx64)
	def enc_jmpx(self):
		return self.__encode_grp_0_instr(self.InstrGrp0Oper.Jmpx)
	def enc_jfal(self):
		return self.__encode_grp_0_instr(self.InstrGrp0Oper.Jfal)
	def enc_jtru(self):
		return self.__encode_grp_0_instr(self.InstrGrp0Oper.Jtru)

	def enc_addi(self, simm16):
		return self.__encode_grp_1_instr(self.InstrGrp1Oper.Addi, simm16)
	def enc_subi(self, simm16):
		return self.__encode_grp_1_instr(self.InstrGrp1Oper.Subi, simm16)
	def enc_muli(self, simm16):
		return self.__encode_grp_1_instr(self.InstrGrp1Oper.Muli, simm16)
	def enc_udivi(self, simm16):
		return self.__encode_grp_1_instr(self.InstrGrp1Oper.Udivi, simm16)
	def enc_sdivi(self, simm16):
		return self.__encode_grp_1_instr(self.InstrGrp1Oper.Sdivi, simm16)
	def enc_umodi(self, simm16):
		return self.__encode_grp_1_instr(self.InstrGrp1Oper.Umodi, simm16)
	def enc_smodi(self, simm16):
		return self.__encode_grp_1_instr(self.InstrGrp1Oper.Smodi, simm16)
	def enc_uslti(self, simm16):
		return self.__encode_grp_1_instr(self.InstrGrp1Oper.Uslti, simm16)
	def enc_sslti(self, simm16):
		return self.__encode_grp_1_instr(self.InstrGrp1Oper.Sslti, simm16)
	def enc_andi(self, simm16):
		return self.__encode_grp_1_instr(self.InstrGrp1Oper.Andi, simm16)
	def enc_ori(self, simm16):
		return self.__encode_grp_1_instr(self.InstrGrp1Oper.Ori, simm16)
	def enc_xori(self, simm16):
		return self.__encode_grp_1_instr(self.InstrGrp1Oper.Xori, simm16)
	def enc_lsli(self, simm16):
		return self.__encode_grp_1_instr(self.InstrGrp1Oper.Lsli, simm16)
	def enc_lsri(self, simm16):
		return self.__encode_grp_1_instr(self.InstrGrp1Oper.Lsri, simm16)
	def enc_asri(self, simm16):
		return self.__encode_grp_1_instr(self.InstrGrp1Oper.Asri, simm16)
	def enc_ldux8i(self, simm16):
		return self.__encode_grp_1_instr(self.InstrGrp1Oper.Ldux8i, simm16)
	def enc_ldsx8i(self, simm16):
		return self.__encode_grp_1_instr(self.InstrGrp1Oper.Ldsx8i, simm16)
	def enc_ldux16i(self, simm16):
		return self.__encode_grp_1_instr(self.InstrGrp1Oper.Ldux16i,
			simm16)
	def enc_ldsx16i(self, simm16):
		return self.__encode_grp_1_instr(self.InstrGrp1Oper.Ldsx16i,
			simm16)
	def enc_ldux32i(self, simm16):
		return self.__encode_grp_1_instr(self.InstrGrp1Oper.Ldux32i,
			simm16)
	def enc_ldsx32i(self, simm16):
		return self.__encode_grp_1_instr(self.InstrGrp1Oper.Ldsx32i,
			simm16)
	def enc_ldx64i(self, simm16):
		return self.__encode_grp_1_instr(self.InstrGrp1Oper.Ldx64i, simm16)
	def enc_stx8i(self, simm16):
		return self.__encode_grp_1_instr(self.InstrGrp1Oper.Stx8i, simm16)
	def enc_stx16i(self, simm16):
		return self.__encode_grp_1_instr(self.InstrGrp1Oper.Stx16i, simm16)
	def enc_stx32i(self, simm16):
		return self.__encode_grp_1_instr(self.InstrGrp1Oper.Stx32i, simm16)
	def enc_stx64i(self, simm16):
		return self.__encode_grp_1_instr(self.InstrGrp1Oper.Stx64i, simm16)
	def enc_jmpxi(self, simm16):
		return self.__encode_grp_1_instr(self.InstrGrp1Oper.Jmpxi, simm16)
	def enc_bfal(self, simm16):
		return self.__encode_grp_1_instr(self.InstrGrp1Oper.Bfal,
			(self.pc() - simm16))
	def enc_btru(self, simm16):
		return self.__encode_grp_1_instr(self.InstrGrp1Oper.Btru,
			(self.pc() - simm16))

	def enc_constu8(self, immediate):
		return self.__encode_grp_2_instr(self.InstrGrp2Oper.Constu8,
			immediate)
	def enc_consts8(self, immediate):
		return self.__encode_grp_2_instr(self.InstrGrp2Oper.Consts8,
			immediate)
	def enc_constu16(self, immediate):
		return self.__encode_grp_2_instr(self.InstrGrp2Oper.Constu16,
			immediate)
	def enc_consts16(self, immediate):
		return self.__encode_grp_2_instr(self.InstrGrp2Oper.Consts16,
			immediate)
	def enc_constu32(self, immediate):
		return self.__encode_grp_2_instr(self.InstrGrp2Oper.Constu32,
			immediate)
	def enc_consts32(self, immediate):
		return self.__encode_grp_2_instr(self.InstrGrp2Oper.Consts32,
			immediate)
	def enc_const64(self, immediate):
		return self.__encode_grp_2_instr(self.InstrGrp2Oper.Const64,
			immediate)

	def enc_arg(self):
		return self.__encode_grp_3_instr(self.InstrGrp3Oper.Arg)
	def enc_var(self):
		return self.__encode_grp_3_instr(self.InstrGrp3Oper.Var)
	def enc_get_pc(self):
		return self.__encode_grp_3_instr(self.InstrGrp3Oper.GetPc)

	def enc_argx(self):
		return self.__encode_grp_4_instr(self.InstrGrp4Oper.Argx)
	def enc_varx(self):
		return self.__encode_grp_4_instr(self.InstrGrp4Oper.Varx)
	def enc_add_to_sp(self):
		return self.__encode_grp_4_instr(self.InstrGrp4Oper.AddToSp)
	def enc_call(self):
		return self.__encode_grp_4_instr(self.InstrGrp4Oper.Call)
	def enc_ret(self):
		return self.__encode_grp_4_instr(self.InstrGrp4Oper.Ret)
	def enc_syscall(self):
		return self.__encode_grp_4_instr(self.InstrGrp4Oper.Syscall)

	def enc_disp_char_syscall(self):
		ret = self.enc_const64(self.SystemCall.DispChar)
		self.enc_syscall()
		return ret

	def enc_disp_str_syscall(self):
		ret = self.enc_const64(self.SystemCall.DispStr)
		self.enc_syscall()
		return ret

	def enc_disp_uint_syscall(self):
		ret = self.enc_const64(self.SystemCall.DispUInt)
		self.enc_syscall()
		return ret
	def enc_disp_sint_syscall(self):
		ret = self.enc_const64(self.SystemCall.DispSInt)
		self.enc_syscall()
		return ret

	def enc_exit_syscall(self):
		ret = self.enc_const64(self.SystemCall.Exit)
		self.enc_syscall()
		return ret

	class InstrGrp0Oper(IntEnum):
		Add = 0
		Sub = auto()
		Mul = auto()
		Udiv = auto()
		Sdiv = auto()
		Umod = auto()
		Smod = auto()
		Uslt = auto()
		Sslt = auto()
		And = auto()
		Or = auto()
		Xor = auto()
		Lsl = auto()
		Lsr = auto()
		Asr = auto()
		Ldux8 = auto()
		Ldsx8 = auto()
		Ldux16 = auto()
		Ldsx16 = auto()
		Ldux32 = auto()
		Ldsx32 = auto()
		Ldx64 = auto()
		Stx8 = auto()
		Stx16 = auto()
		Stx32 = auto()
		Stx64 = auto()
		Jmpx = auto()
		Jfal = auto()
		Jtru = auto()
	class InstrGrp1Oper(IntEnum):
		Addi = 0
		Subi = auto()
		Muli = auto()
		Udivi = auto()
		Sdivi = auto()
		Umodi = auto()
		Smodi = auto()
		Uslti = auto()
		Sslti = auto()
		Andi = auto()
		Ori = auto()
		Xori = auto()
		Lsli = auto()
		Lsri = auto()
		Asri = auto()
		Ldux8i = auto()
		Ldsx8i = auto()
		Ldux16i = auto()
		Ldsx16i = auto()
		Ldux32i = auto()
		Ldsx32i = auto()
		Ldx64i = auto()
		Stx8i = auto()
		Stx16i = auto()
		Stx32i = auto()
		Stx64i = auto()
		Jmpxi = auto()
		Bfal = auto()
		Btru = auto()
	class InstrGrp2Oper(IntEnum):
		Constu8 = 0
		Consts8 = auto()
		Constu16 = auto()
		Consts16 = auto()
		Constu32 = auto()
		Consts32 = auto()
		Const64 = auto()
	class InstrGrp3Oper(IntEnum):
		Arg = 0
		Var = auto()
		GetPc = auto()
	class InstrGrp4Oper(IntEnum):
		Argx = 0
		Varx = auto()
		AddToSp = auto()
		Call = auto()
		Ret = auto()
		Syscall = auto()
	class SystemCall(IntEnum):
		DispChar = 0
		DispStr = auto()
		DispUInt = auto()
		DispSInt = auto()
		Exit = auto()

