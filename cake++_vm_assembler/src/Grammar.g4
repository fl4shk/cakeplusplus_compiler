grammar Grammar;

// Parser rules
program:
	line*
	;

line:
	label (comment?) '\n'
	| instruction (comment?) '\n'
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
	| instrNoImmArgs
	| instrBeq | instrBne
	| instrBeqNear | instrBneNear
	| instrBinop
	;


instrConst:
	'[const(' expr ')]'
	;

instrConstU32:
	'[const_u32(' expr ')]'
	;
instrConstS32:
	'[const_s32(' expr ')]'
	;
instrConstU16:
	'[const_u16(' expr ')]'
	;
instrConstS16:
	'[const_s16(' expr ')]'
	;
instrConstU8:
	'[const_u8(' expr ')]'
	;
instrConstS8:
	'[const_s8(' expr ')]'
	;

instrNoImmArgs:
	TokNoImmArgsOp
	;

instrBeq:
	'[beq(' expr ')]'
	;
instrBne:
	'[bne(' expr ')]'
	;
instrBeqNear:
	'[beq_near(' expr ')]'
	;
instrBneNear:
	'[bne_near(' expr ')]'
	;
instrBinop:
	TokBinOp
	;


comment:
	';' (~ '\n')*
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
	exprUnary
	| numExpr
	| identName
	| currPc
	| '(' expr ')'
	//| TokOpUnary expr
	;

exprUnary:
	exprBitInvert
	| exprNegate
	| exprLogNegate
	;

exprBitInvert:
	'~' expr
	;
exprNegate:
	'-' expr
	;
exprLogNegate:
	'!' expr
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
fragment LexLeftBracket:
	'['
	;
fragment LexRightBracket:
	']'
	;
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
	LexLeftBracket LexLdPrefix LexBuiltinTypename LexRightBracket
	;
TokLdxOp:
	LexLeftBracket LexLdxPrefix LexBuiltinTypename LexRightBracket
	;
TokStOp:
	LexLeftBracket LexStPrefix LexBuiltinTypename LexRightBracket
	;
TokStxOp:
	LexLeftBracket LexStxPrefix LexBuiltinTypename LexRightBracket
	;

TokNoImmArgsOp: 
	('[arg]' | '[argx]' | '[var]' | '[varx]'
	| '[get_pc]' | '[jump]'
	| '[call]' | '[ret]'
	| TokLdOp | TokLdxOp | TokStOp | TokStxOp
	| '[add_to_sp]'
	| '[disp_num]' | '[disp_num_unsigned]' | '[disp_char]' | '[disp_str]'
	| '[get_num]'
	| '[quit]')
	;


TokBinOp:
	('[add]' | '[sub]' | '[mul]' 
	| '[udiv]' | '[sdiv]' | '[umod]' | '[smod]' 
	| '[bit_and]' | '[bit_or]' | '[bit_xor]' 
	| '[bit_lsl]' | '[bit_lsr]' | '[bit_asr]' 
	| '[cmp_eq]' | '[cmp_ne]' 
	| '[cmp_ult]' | '[cmp_slt]' | '[cmp_ugt]' | '[cmp_sgt]' 
	| '[cmp_ule]' | '[cmp_sle]' | '[cmp_uge]' | '[cmp_sge]')
	;

TokOpLogical: ('&&' | '||') ;
TokOpCompare: ('==' | '!=' | '<' | '>' | '<=' | '>=') ;
TokOpAddSub: ('+' | '-') ;
TokOpMulDivMod: ('*' | '/' | '%') ;
TokOpBitwise: ('&' | '|' | '^' | '<<' | '>>' | '>>>') ;
//TokOpUnary: ('~' | '-' | '!') ;
TokDecNum: [0-9] ([0-9]*) ;
TokIdent: [A-Za-z_] (([A-Za-z_] | [0-9])*) ;
