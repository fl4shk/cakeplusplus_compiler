main:
{
	; Allocate space for exit code
	const_u8(0)
	;const_u8(88)



	; Allocate space for return value
	const_u8(0)

	; Subtract 8 from 9
	const_u8(9)
	const_u8(8)

	.calli(sub)
	;.calli(add)

	const_s8(-16)
	add_to_sp

	disp_num
	.calli(disp_newline)


	quit
}


; s64 add(s64 a, s64 b)
add:
{
	; Load a
	arg
	ld_basic


	; Load b
	const_s8(-8)
	argx
	ld_basic


	; Perform the addition
	add

	; Address of return value
	const_s8(-16)
	argx

	; Store return value
	st_basic


	ret
}


; s64 sub(s64 a, s64 b)
sub:
{
	; Load a
	arg
	ld_basic


	; Load b
	const_s8(-8)
	argx
	ld_basic


	; Perform the subtraction
	sub

	; Address of return value
	const_s8(-16)
	argx

	; Store return value
	st_basic


	ret
}



disp_newline:
{
	const_u8(10)
	disp_char
	ret
}



test_arr_dim:
	.space 8

test_arr_data:
	.space (8 * 20)



egg:
	.db 10
	.db_u32 9
	.db_u16 -1
