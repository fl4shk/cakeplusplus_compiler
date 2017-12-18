main:
	; Allocate space for return value
	const(0)

	; Arguments
	const(8)
	const(9)

	;; Function label
	;const(add)
	;call
	;const_s8(-16)
	;add_to_sp

	add

	disp_num


	const(0)
	quit


;add:
;	const_s8(-8)
;	argx
;	ld_basic
;
;	arg
;	ld_basic
;
;	add
;
;	; return value
;	const_s8(-16)
;	argx
;	st_basic
;
;
;
;	ret
