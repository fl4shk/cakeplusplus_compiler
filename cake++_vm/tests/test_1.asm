main:
	; Allocate space for return value
	const_u8(0)

	; Arguments
	const_u8(8)
	const_u8(9)

	; Function label
	const(add)
	call
	const_s8(-16)
	add_to_sp


	;const(9)
	disp_num

	.calli(disp_newline)


	const(0)
	quit

disp_newline:
	const_u8(10)
	disp_char
	ret

add:
	arg
	ld_basic
	disp_num

	.calli(disp_newline)

	const_s8(-8)
	argx
	ld_basic
	disp_num

	.calli(disp_newline)

	; Perform the actual add now
	const_s8(-8)
	argx
	ld_basic

	arg
	ld_basic

	add

	; return value
	const_s8(-16)
	argx
	st_basic


	ret


arr:
	.space 20

egg:
	.db 10
	.db_u32 9
	.db_u16 -1
