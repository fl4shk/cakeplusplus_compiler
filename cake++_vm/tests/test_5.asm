		const_u8(0)
		const(main)
		call


		disp_num

		const_u8(10)
		disp_char

		const_u8(0)

		quit
main:
;{
		const(32)
		add_to_sp

		const(3)
		var
		st_basic


			var
			ld_basic
			const_u8(8)
		mul

			const_u8(8)
		add

		arg
		st_basic

		const(-32)
		add_to_sp
		ret

;}
;get_size:
;;{
;		const_u8(8)
;		arg
;		ld_basic
;		const_u8(8)
;		mul
;		add
;		const(-8)
;		argx
;		st_basic
;		const_u8(0)
;		beq(_1)
;	_1:
;		ret
;;}
