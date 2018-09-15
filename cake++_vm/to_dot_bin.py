#! /usr/bin/env python3

f = open("input.bin", mode="wb")

def __write_bytes(some_list):
	f.write(bytes(some_list))

def write_8_bit(some_int):
	__write_bytes([some_int & 0xff])

def write_16_bit(some_int):
	__write_bytes([(some_int >> 8) & 0xff, some_int & 0xff])

def write_32_bit(some_int):
	__write_16_bit(some_int >> 16)
	__write_16_bit(some_int)

def write_64_bit(some_int):
	__write_32_bit(some_int >> 32)
	__write_32_bit(some_int)

def instr_constu8(num):
	write_16_bit(0x0200)
	write_8_bit(num)
def instr_consts8(num):
	write_16_bit(0x0201)
	write_8_bit(num)
def instr_constu16(num):
	write_16_bit(0x0202)
	write_16_bit(num)
def instr_consts16(num):
	write_16_bit(0x0203)
	write_16_bit(num)
def instr_constu32(num):
	write_16_bit(0x0204)
	write_32_bit(num)
def instr_consts32(num):
	write_16_bit(0x0205)
	write_32_bit(num)
def instr_const64(num):
	write_16_bit(0x0206)
	write_64_bit(num)

def instr_add(): write_16_bit(0x0000)
def instr_sub(): write_16_bit(0x0001)
def instr_mul(): write_16_bit(0x0002)
def instr_udiv(): write_16_bit(0x0003)
def instr_sdiv(): write_16_bit(0x0004)
def instr_umod(): write_16_bit(0x0005)
def instr_smod(): write_16_bit(0x0006)
def instr_uslt(): write_16_bit(0x0007)
def instr_sslt(): write_16_bit(0x0008)
def instr_and(): write_16_bit(0x0009)
def instr_or(): write_16_bit(0x000a)
def instr_xor(): write_16_bit(0x000b)
def instr_lsl(): write_16_bit(0x000c)
def instr_lsr(): write_16_bit(0x000d)
def instr_asr(): write_16_bit(0x000e)

def syscall(): write_16_bit(0x0405)

def disp_char_syscall():
	instr_constu8(0x00)
	syscall()

def disp_uint_syscall():
	instr_constu8(0x02)
	syscall()
def disp_sint_syscall():
	instr_constu8(0x03)
	syscall()

def exit_syscall():
	instr_constu8(0x04)
	syscall()


to_print = "Banks wants to empty the banks,"
to_print += " fill our streets with banks,"
to_print += " and run a bank-making operation out of his banks."
to_print += "\n"
for c in to_print:
	instr_constu8(ord(c))
	disp_char_syscall()


instr_constu16(5)
instr_constu16(90)
instr_add()
disp_uint_syscall()

instr_constu8(ord("\n"))
disp_char_syscall()

instr_constu16(9001)
exit_syscall()
