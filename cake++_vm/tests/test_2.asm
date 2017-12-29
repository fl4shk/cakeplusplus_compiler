start:
{
	; Allocate space for exit code
	const_u8(0)
	;const_u8(88)


	.calli(main)


	quit
}

main:
{
	const_s16(50 * 8)
	add_to_sp



	const(97)
	const(16)
	var
	stx_basic
	;const(16)
	;varx
	;st_basic


	;const(16)
	;;varx
	;;ld_basic
	;var
	;add
	;ld_basic
	;const(16)


	disp_char
	.calli(disp_newline)






	const_s16(-(50 * 8))
	add_to_sp

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
