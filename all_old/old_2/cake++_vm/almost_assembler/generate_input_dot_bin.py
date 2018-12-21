#! /usr/bin/env python3

from almost_assembler import Blank, sconcat, AlmostAssembler




asm = AlmostAssembler()

def patch_in_null_terminated_str(paste_loc, to_paste):
	for c in to_paste:
		asm.patch_byte_raw(paste_loc, ord(c))
		paste_loc += 1
	asm.patch_byte_raw(paste_loc, 0)


def start_func():
	return asm.pc()





# Jump over "fill_our_streets"
asm.enc_constu8(0)
patch_loc = asm.enc_raw_bfal(0)




fill_our_streets = asm.paste_null_terminated_str \
	("Banks wants to empty the banks," + " fill our streets with banks,"
	+ " and run a bank-making operation out of his banks." + "\n")

show_me_your_moves = asm.paste_null_terminated_str("Show me your moves!")



func_disp_str_with_disp_char_syscall = start_func()

# void disp_str_with_disp_char_syscall(char* str)
# {
# 	do
# 	{
# 		disp_char(*str);
# 		++str;
# 	} while ((*str) != '\0');
# }


#asm.enc_const64(asm.pc())
#asm.enc_get_pc()



# disp_char(*str);
asm.enc_arg()
asm.enc_ldx64i(0)
asm.enc_ldxu8i(0)
asm.enc_disp_char_syscall()


# ++str;
asm.enc_arg()
asm.enc_ldx64i(0)
asm.enc_addi(1)
asm.enc_arg()
asm.enc_stx64i(0)


# branch when ((*str) != '\0')
asm.enc_arg()
asm.enc_ldx64i(0)
asm.enc_ldxu8i(0)

asm.enc_backwards_btru(func_disp_str_with_disp_char_syscall)

#asm.enc_jtru()



# Return
asm.enc_ret()




jump_loc = asm.EncodedInstrPcs(asm.pc(), 0, 0)
asm.patch_relative_branch(patch_loc, jump_loc)


asm.enc_const64(fill_our_streets)
#asm.enc_disp_str_syscall()
asm.enc_const64(func_disp_str_with_disp_char_syscall)
asm.enc_call()










# Allocate space for return value
asm.enc_const64(8)
asm.enc_add_to_sp()




# arguments to the function
# Compute 333 / 9
asm.enc_const64(333)
asm.enc_const64(9)



patch_func_udiv = asm.enc_const64(0)
asm.enc_call()



asm.enc_consts8(-16)
asm.enc_add_to_sp()
asm.enc_disp_uint_syscall()


asm.enc_constu8(ord("\n"))
asm.enc_disp_char_syscall()


asm.enc_constu16(9001)
asm.enc_exit_syscall()





func_udiv = start_func()
asm.patch_instr_arg_eight_bytes(patch_func_udiv, func_udiv)

# argument 1
asm.enc_arg()
asm.enc_ldx64i(0)


# argument 0
asm.enc_arg()
asm.enc_consts8(-8)
asm.enc_ldx64()


# push(arg_0 udiv arg_1)
asm.enc_udiv()


# return val address
asm.enc_consts8(-16)
asm.enc_arg()

# store to the return value
asm.enc_stx64()

asm.enc_ret()




asm.finalize()
