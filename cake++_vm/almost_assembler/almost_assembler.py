#! /usr/bin/env python3

from helpers import Blank, sconcat, AlmostAssembler




asm = AlmostAssembler()

def patch_in_null_terminated_str(paste_loc, to_paste):
	for c in to_paste:
		asm.patch_byte_raw(paste_loc, ord(c))
		paste_loc += 1
	asm.patch_byte_raw(paste_loc, 0)


def start_func():
	return asm.pc()




asm.enc_constu8(0)
patch_loc = asm.enc_bfal(0)



func_udiv = start_func()


# argument 0
asm.enc_consts8(-8)
asm.enc_argx()
asm.enc_ldx64i(0)

# argument 1
asm.enc_arg()
asm.enc_ldx64i(0)


# push(arg_0 udiv arg_1)
asm.enc_udiv()

# return val address
asm.enc_consts8(-16)
asm.enc_argx()

# store to the return value
asm.enc_stx64i(0)

asm.enc_ret()








#fill_our_streets = asm.paste_null_terminated_str \
#	("Banks wants to empty the banks," + " fill our streets with banks,"
#	+ " and run a bank-making operation out of his banks." + "\n")



jump_loc = asm.EncodedInstrPcs(asm.pc(), 0, 0)

#asm.enc_const64(fill_our_streets)
#asm.enc_disp_str_syscall()


asm.patch_relative_branch(patch_loc, jump_loc)





# Allocate space for return value
asm.enc_const64(8)
asm.enc_add_to_sp()




# arguments to the function
# Compute 333 / 9
asm.enc_const64(9)
asm.enc_const64(333)


asm.enc_const64(func_udiv)
asm.enc_call()



asm.enc_consts8(-16)
asm.enc_add_to_sp()




asm.enc_disp_uint_syscall()


asm.enc_constu16(9001)
asm.enc_exit_syscall()



asm.finalize()
