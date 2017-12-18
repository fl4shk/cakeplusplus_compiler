main:
	const(7)

	; Allocate space for return value
	const(0)

	; Arguments
	const(8)
	const(9)

	; Function label
	const(add)
	call
	const_s8(-16)
	add_to_sp


	;const(9)
	disp_num

	const_u8(10)
	disp_char


	const(0)
	quit


add:
	arg
	ld_basic
	;disp_num

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
