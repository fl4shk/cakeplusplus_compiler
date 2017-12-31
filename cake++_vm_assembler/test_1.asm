main:
{
		;.db_u16 _0
	_0:
		;const_u8(0)
		;bne(_0)
		;.db_u16 _0
		;const_u8(0)
		;bne(_0)
		;.db_u16 _0

		;const_u8(0)
		;bne(_0)

		;bne(egg)
		.db_u8 _0
	_egg:

		;const(_egg)
		;bne(_egg)
		;.db_u8 _egg
		const_u8(0)
		bne_near(_egg)
		call

	.db egg
}

egg:
{
	.db egg
	;	;.db_u16 egg
	;	;.db_u16 _0
	;_0:
	;	const_u8(0)
	;	bne(_0)
}

jorge:
{
	.db egg
}
