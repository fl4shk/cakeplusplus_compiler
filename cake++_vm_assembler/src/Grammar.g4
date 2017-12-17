grammar Grammar;

// Parser rules
program:
	line*
	;

line:
	label '\n'
	| instruction '\n'
	| comment '\n'
	| '\n'
	;

label:
	identName ':'
	;

instruction:
	instrConst
	| instrConstU32 | instrConstS32
	| instrConstU16 | instrConstS16
	| instrConstU8 | instrConstS8
	| instrArg | instrArgX
	| instrVar | instrVarX
	| instrGetPc | instrJump
	| instrBeq | instrBne
	| instrBeqNear | instrBneNear
	| instrCall | instrRet
	| instrLd | instrLdx | instrSt | instrStx
	| instrBinop
	| instrDispNum | instrDispNumUnsigned
	| instrDispChar | instrDispStr
	| instrGetNum
	| instrQuit
	;


instrConst:
	'const(' expr ')'
	;

instrConstU32:
	'const_u32(' expr ')'
	;
instrConstS32:
	'const_s32(' expr ')'
	;
instrConstU16:
	'const_u16(' expr ')'
	;
instrConstS16:
	'const_s16(' expr ')'
	;
instrConstU8:
	'const_u8(' expr ')'
	;
instrConstS8:
	'const_s8(' expr ')'
	;

instrArg:
	'arg'
	;
instrArgX:
	'argx'
	;
instrVar:
	'var'
	;
instrVarX:
	'varx'
	;
instrGetPc:
	'get_pc'
	;
instrJump:
	'jump'
	;
instrBeq:
	'beq(' expr ')'
	;
instrBne:
	'bne(' expr ')'
	;
instrBeqNear:
	'beq_near(' expr ')'
	;
instrBneNear:
	'bne_near(' expr ')'
	;
instrCall:
	'call(' identName ')'
	| 'call(' expr ')'
	;
instrRet:
	'ret'
	;
instrLd:
	TokLdOp
	;
instrLdx:
	TokLdxOp
	;
instrSt:
	TokStOp
	;
instrStx:
	TokStxOp
	;
instrBinop:
	TokBinOp
	;
instrDispNum:
	'disp_num'
	;
instrDispNumUnsigned:
	'disp_num_unsigned'
	;
instrDispChar:
	'disp_char'
	;
instrDispStr:
	'disp_str'
	;
instrGetNum:
	'get_num'
	;
instrQuit:
	'quit'
	;


comment:
	';' TokNonNewline*
	;

expr:
	exprLogical
	| expr TokOpLogical exprLogical
	;

exprLogical:
	exprCompare
	| exprLogical TokOpCompare exprCompare
	;

exprCompare:
	exprAddSub
	| exprCompare TokOpAddSub exprAddSub
	;

exprAddSub:
	exprMulDivModEtc
	| exprAddSub TokOpMulDivMod exprMulDivModEtc
	| exprAddSub TokOpBitwise exprMulDivModEtc
	;

exprMulDivModEtc:
	numExpr
	| identName
	| currPc
	| '(' expr ')'
	| TokOpUnary expr
	;

identName:
	TokIdent
	;

numExpr:
	TokDecNum
	;

currPc:
	'.'
	;



// Lexer rules
LexWhitespace: (' ' | '\t') -> skip ;
fragment LexBuiltinTypename: 
	('basic' | 'u32' | 's32' | 'u16' | 's16' | 'u8' | 's8')
	;

fragment LexLdPrefix:
	'ld_'
	;
fragment LexLdxPrefix:
	'ldx_'
	;
fragment LexStPrefix:
	'st_'
	;
fragment LexStxPrefix:
	'stx_'
	;

TokLdOp:
	LexLdPrefix LexBuiltinTypename
	;
TokLdxOp:
	LexLdxPrefix LexBuiltinTypename
	;
TokStOp:
	LexStPrefix LexBuiltinTypename
	;
TokStxOp:
	LexStxPrefix LexBuiltinTypename
	;

TokBinOp:
	( 'add' | 'sub' | 'mul' | 'sdiv' | 'udiv' | 'smod' | 'umod' 
	| 'bit_and' | 'bit_or' | 'bit_xor' | 'bit_lsl' | 'bit_lsr' | 'bit_asr' 
	| 'cmp_eq' | 'cmp_ne' 
	| 'cmp_ult' | 'cmp_slt' | 'cmp_ugt' | 'cmp_sgt' 
	| 'cmp_ule' | 'cmp_sle' | 'cmp_uge' | 'cmp_sge')
	;

TokOpLogical: ('&&' | '||') ;
TokOpCompare: ('==' | '!=' | '<' | '>' | '<=' | '>=') ;
TokOpAddSub: ('+' | '-') ;
TokOpMulDivMod: ('*' | '/' | '%') ;
TokOpBitwise: ('&' | '|' | '^' | '<<' | '>>' | '>>>') ;
TokOpUnary: ('~' | '-' | '!') ;
TokDecNum: [0-9] ([0-9]*) ;
TokIdent: [A-Za-z_] (([A-Za-z_] | [0-9])*) ;
TokNonNewline: [^\n]
	;
