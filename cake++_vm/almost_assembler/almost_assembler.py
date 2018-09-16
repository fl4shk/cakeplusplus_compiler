#! /usr/bin/env python3

from enum import IntEnum, auto

class Blank:
	def __init__(self):
		pass

def sconcat(*args):
	ret = ""
	for arg in args:
		ret += str(arg)
	return ret


class AlmostAssembler:
	def __init__(self):
		self.__pc = 0
		self.__encoded_bytes = []

	def finalize(self):
		f = open("input.bin", mode="wb")
		f.write(bytes(self.__encoded_bytes))

	def pc(self):
		return self.__pc


	class EncodedInstrPcs:
		def __init__(self, header_pc, arg_pc, num_arg_bytes):
			self.__header_pc = header_pc
			self.__arg_pc = arg_pc
			self.__num_arg_bytes = num_arg_bytes

		def header_pc(self):
			return self.__header_pc
		def arg_pc(self):
			return self.__arg_pc
		def num_arg_bytes(self):
			return self.__num_arg_bytes

	def alloc(self, amount):
		ret = self.__pc

		for i in range(amount):
			self.__write_next_byte(0)

		return ret

	def alloc_for_null_terminated_str(self, to_alloc_for):
		return self.alloc(len(to_alloc_for) + 1)


	def paste_null_terminated_str(self, to_paste):
		ret = self.__pc
		for c in to_paste:
			self.__write_next_byte(ord(c))

		# Null terminate
		self.__write_next_byte(0)
		return ret


	def patch_byte_raw(self, where, some_int):
		self.__encoded_bytes[where] = (some_int & 0xff)

	def patch_two_bytes_raw(self, where, some_int):
		self.patch_byte_raw(where, (some_int >> 8))
		self.patch_byte_raw((where + 1), some_int)
	def patch_four_bytes_raw(self, where, some_int):
		self.patch_two_bytes_raw(where, (some_int >> 16))
		self.patch_two_bytes_raw((where + 2), some_int)
	def patch_eight_bytes_raw(self, where, some_int):
		self.patch_four_bytes_raw(where, (some_int >> 32))
		self.patch_four_bytes_raw((where + 4), some_int)

	def patch_instr_arg_byte(self, some_encoded_instr_pcs, some_int):
		if (some_encoded_instr_pcs.num_arg_bytes() != 1):
			print(sconcat("Error in args to ",
				"AlmostAssembler.patch_instr_arg_byte()"))
			exit(1)

		where = some_encoded_instr_pcs.arg_pc()
		self.patch_byte_raw(where, some_int)

	def patch_instr_arg_two_bytes(self, some_encoded_instr_pcs, some_int):
		if (some_encoded_instr_pcs.num_arg_bytes() != 2):
			print(sconcat("Error in args to ",
				"AlmostAssembler.patch_instr_arg_two_bytes()"))
			exit(1)

		where = some_encoded_instr_pcs.arg_pc()
		self.patch_two_bytes_raw(where, some_int)
	def patch_instr_arg_four_bytes(self, some_encoded_instr_pcs, some_int):
		if (some_encoded_instr_pcs.num_arg_bytes() != 4):
			print(sconcat("Error in args to ",
				"AlmostAssembler.patch_instr_arg_four_bytes()"))
			exit(1)

		where = some_encoded_instr_pcs.arg_pc()
		self.patch_four_bytes_raw(where, some_int)
	def patch_instr_arg_eight_bytes(self, some_encoded_instr_pcs, some_int):
		if (some_encoded_instr_pcs.num_arg_bytes() != 8):
			print(sconcat("Error in args to ",
				"AlmostAssembler.patch_instr_arg_eight_bytes()"))
			exit(1)

		where = some_encoded_instr_pcs.arg_pc()
		self.patch_eight_bytes_raw(where, some_int)

	def patch_relative_branch(self, patch_loc, jump_loc):
		self.patch_instr_arg_two_bytes(patch_loc,
			(jump_loc.header_pc() - patch_loc.header_pc() - 4))



	def __write_next_byte(self, some_int):
		ret = self.__pc
		self.__pc += 1
		self.__encoded_bytes.append(some_int & 0xff)
		return ret

	def __write_next_two_bytes(self, some_int):
		ret = self.__write_next_byte(some_int >> 8)
		self.__write_next_byte(some_int)
		return ret

	def __write_next_four_bytes(self, some_int):
		ret = self.__write_next_two_bytes(some_int >> 16)
		self.__write_next_two_bytes(some_int)
		return ret

	def __write_next_eight_bytes(self, some_int):
		ret = self.__write_next_four_bytes(some_int >> 32)
		self.__write_next_four_bytes(some_int)
		return ret

	def __encode_instr_header(self, group, oper):
		ret = self.__write_next_byte(group)
		self.__write_next_byte(oper)
		return ret

	def __encode_grp_0_instr(self, oper):
		temp = self.__encode_instr_header(0, oper)
		return self.EncodedInstrPcs(temp, 0, 0)

	def __encode_grp_1_instr(self, oper, simm16):
		temp_0 = self.__encode_instr_header(1, oper)
		temp_1 = self.__write_next_two_bytes(simm16)
		return self.EncodedInstrPcs(temp_0, temp_1, 2)

	def __encode_grp_2_instr(self, oper, immediate):
		temp_0 = self.__encode_instr_header(2, oper)
		temp_1 = 0
		num_arg_bytes = 0

		if ((oper == self.InstrGrp2Oper.Constu8)
			or (oper == self.InstrGrp2Oper.Consts8)):
			temp_1 = self.__write_next_byte(immediate)
			num_arg_bytes = 1
		elif ((oper == self.InstrGrp2Oper.Constu16)
			or (oper == self.InstrGrp2Oper.Consts16)):
			temp_1 = self.__write_next_two_bytes(immediate)
			num_arg_bytes = 2
		elif ((oper == self.InstrGrp2Oper.Constu32)
			or (oper == self.InstrGrp2Oper.Consts32)):
			temp_1 = self.__write_next_four_bytes(immediate)
			num_arg_bytes = 4
		elif (oper == self.InstrGrp2Oper.Const64):
			temp_1 = self.__write_next_eight_bytes(immediate)
			num_arg_bytes = 8

		return self.EncodedInstrPcs(temp_0, temp_1, num_arg_bytes)

	def __encode_grp_3_instr(self, oper):
		temp = self.__encode_instr_header(3, oper)
		return self.EncodedInstrPcs(temp, temp, 0)
	def __encode_grp_4_instr(self, oper):
		temp = self.__encode_instr_header(4, oper)
		return self.EncodedInstrPcs(temp, temp, 0)

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
	def enc_ldxu8(self):
		return self.__encode_grp_0_instr(self.InstrGrp0Oper.Ldxu8)
	def enc_ldxs8(self):
		return self.__encode_grp_0_instr(self.InstrGrp0Oper.Ldxs8)
	def enc_ldxu16(self):
		return self.__encode_grp_0_instr(self.InstrGrp0Oper.Ldxu16)
	def enc_ldxs16(self):
		return self.__encode_grp_0_instr(self.InstrGrp0Oper.Ldxs16)
	def enc_ldxu32(self):
		return self.__encode_grp_0_instr(self.InstrGrp0Oper.Ldxu32)
	def enc_ldxs32(self):
		return self.__encode_grp_0_instr(self.InstrGrp0Oper.Ldxs32)
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
	def enc_ldxu8i(self, simm16):
		return self.__encode_grp_1_instr(self.InstrGrp1Oper.Ldxu8i, simm16)
	def enc_ldxs8i(self, simm16):
		return self.__encode_grp_1_instr(self.InstrGrp1Oper.Ldxs8i, simm16)
	def enc_ldxu16i(self, simm16):
		return self.__encode_grp_1_instr(self.InstrGrp1Oper.Ldxu16i,
			simm16)
	def enc_ldxs16i(self, simm16):
		return self.__encode_grp_1_instr(self.InstrGrp1Oper.Ldxs16i,
			simm16)
	def enc_ldxu32i(self, simm16):
		return self.__encode_grp_1_instr(self.InstrGrp1Oper.Ldxu32i,
			simm16)
	def enc_ldxs32i(self, simm16):
		return self.__encode_grp_1_instr(self.InstrGrp1Oper.Ldxs32i,
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
	def enc_raw_bfal(self, simm16):
		return self.__encode_grp_1_instr(self.InstrGrp1Oper.Bfal, simm16)
	def enc_raw_btru(self, simm16):
		return self.__encode_grp_1_instr(self.InstrGrp1Oper.Btru, simm16)

	def enc_backwards_bfal(self, simm16):
		return self.enc_raw_bfal(simm16 - self.pc() - 4)
	def enc_backwards_btru(self, simm16):
		return self.enc_raw_btru(simm16 - self.pc() - 4)

	#def enc_bfal(self, simm16):
	#	return self.__encode_grp_1_instr(self.InstrGrp1Oper.Bfal,
	#		(self.pc() - simm16))
	#def enc_btru(self, simm16):
	#	return self.__encode_grp_1_instr(self.InstrGrp1Oper.Btru,
	#		(self.pc() - simm16))

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
		Ldxu8 = auto()
		Ldxs8 = auto()
		Ldxu16 = auto()
		Ldxs16 = auto()
		Ldxu32 = auto()
		Ldxs32 = auto()
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
		Ldxu8i = auto()
		Ldxs8i = auto()
		Ldxu16i = auto()
		Ldxs16i = auto()
		Ldxu32i = auto()
		Ldxs32i = auto()
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

