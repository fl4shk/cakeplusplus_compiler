		const_u8(0)
		const(main)
		call
		quit
main:
{
		const(32)
		add_to_sp
		const(3)
		var
		st_basic
		const(3)
		const(0)
		syscall
		const_u8(10)
		const(2)
		syscall
		const_u8(0)
		var
		const(get_size)
		call
		const(-8)
		add_to_sp
		arg
		st_basic
		const_u8(0)
		beq(_0)
	_0:
		const(-32)
		add_to_sp
		ret
}
get_size:
{
		const_u8(8)
		arg
		ld_basic
		ld_basic
		const_u8(8)
		mul
		add
		const(-8)
		argx
		st_basic
		const_u8(0)
		beq(_1)
	_1:
		ret
}
;clear_arr:
;{
;		const(8)
;		add_to_sp
;		const(0)
;		var
;		st_basic
;	_0:
;		var
;		ld_basic
;		arg
;		ld_basic
;		ld_basic
;		cmp_ult
;		beq(_1)
;		const(0)
;		arg
;		ld_basic
;		const_u8(8)
;		add
;		var
;		ld_basic
;		add
;		st_basic
;		var
;		ld_basic
;		const(1)
;		add
;		var
;		st_basic
;		const_u8(0)
;		beq(_0)
;	_1:
;		const_u8(8)
;		arg
;		ld_basic
;		ld_basic
;		const_u8(8)
;		mul
;		add
;		const(-8)
;		argx
;		st_basic
;		const_u8(0)
;		beq(_2)
;	_2:
;		const(-8)
;		add_to_sp
;		ret
;}
