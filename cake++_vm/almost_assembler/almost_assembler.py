#! /usr/bin/env python3

from helpers import AlmostAssembler

class Blank:
	def __init__(self):
		pass

def sconcat(*args):
	ret = ""
	for arg in args:
		ret += str(arg)
	return ret


almost_assembler = AlmostAssembler()


to_print = "Banks wants to empty the banks,"
to_print += " fill our streets with banks,"
to_print += " and run a bank-making operation out of his banks."
to_print += "\n"

#for c in to_print:
#	almost_assembler.enc_constu8(ord(c))
#	almost_assembler.enc_disp_char_syscall()
#
#
#almost_assembler.enc_constu16(5)
#almost_assembler.enc_constu16(94)
#almost_assembler.enc_add()
#almost_assembler.enc_disp_uint_syscall()
#
#almost_assembler.enc_constu8(ord("\n"))
#almost_assembler.enc_disp_char_syscall()
#

almost_assembler.enc_constu16(0x5999)
almost_assembler.enc_constu32(0x15623)
almost_assembler.enc_add()


almost_assembler.enc_constu16(0x9002)
almost_assembler.enc_consts8(-1)
almost_assembler.enc_add()



almost_assembler.enc_stx64i(0)


almost_assembler.enc_constu16(0x9001)
almost_assembler.enc_ldx64i(0)
almost_assembler.enc_disp_uint_syscall()


almost_assembler.enc_constu8(ord("\n"))
almost_assembler.enc_disp_char_syscall()


almost_assembler.enc_constu16(9001)
almost_assembler.enc_exit_syscall()
