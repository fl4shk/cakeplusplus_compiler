		const_u8(0)
		const(main)
		call
		quit
main:
{
		const(54)
		add_to_sp
		const(6)
		var
		st_basic
		const(3)
		const(14)
		varx
		st_basic
		const_u8(0)
		const(22)
		varx
		const(clear_arr)
		call
		const(-8)
		add_to_sp
		const(46)
		varx
		const(0)
		st_basic
	_0:
		const(46)
		varx
		ld_basic
		const(3)
		cmp_ult
		bne(_1)
		const(22)
		varx
		const(46)
		varx
		ld_basic
		add
		const(46)
		varx
		ld_basic
		const(8)
		mul
		st_basic
		const(22)
		varx
		const(46)
		varx
		ld_basic
		add
		ld_basic
		syscall
		const_u8(10)
		syscall
		const(46)
		varx
		const(46)
		varx
		ld_basic
		const(1)
		add
		st_basic
		const_u8(0)
		beq(_0)
	_1:
		const(9000)
		arg
		st_u32
		const_u8(0)
		beq(_2)
	_2:
		const(-54)
		add_to_sp
		ret
}
clear_arr:
{
		const(8)
		add_to_sp
		var
		const(0)
		st_basic
	_0:
		var
		ld_basic
		arg
		ld_basic
		cmp_ult
		bne(_1)
		arg
		var
		ld_basic
		add
		const(0)
		st_basic
		var
		var
		ld_basic
		const(1)
		add
		st_basic
		const_u8(0)
		beq(_0)
	_1:
		const_u8(8)
		arg
		ld_basic
		const_u8(8)
		mul
		add
		const(-8)
		argx
		st_u32
		const_u8(0)
		beq(_2)
	_2:
		const(-8)
		add_to_sp
		ret
}
