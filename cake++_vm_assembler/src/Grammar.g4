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
	instrConstant
	| instrArg | instrArgX
	| instrVar | instrVarX
	| instrGetArgSpace | instrSetArgSpace
	| instrGetPc | instrJump
	| instrBeq | instrBne
	| instrCall | instrRet
	| instrLd | instrLdx | instrSt | instrStx
	| instrBinop
	| instrDispNum | instrDispNumUnsigned
	| instrDispChar | instrDispStr
	| instrGetNum
	| instrQuit
	;


instrConstant:
	'constant(' expr ')'
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
instrGetArgSpace:
	'get_arg_space'
	;
instrSetArgSpace:
	'set_arg_space'
	;
instrGetPc:
	'get_pc'
	;
instrJump:
	'jump'
	;
instrBeq:
	'beq(' identName ')'
	| 'beq(' expr ')'
	;
instrBne:
	'bne(' identName ')'
	| 'bne(' expr ')'
	;
instrCall:
	'call(' identName ')'
	| 'call(' expr ')'
	;
instrRet:
	'ret'
	;
instrLd:
	'ld(' TokBuiltinTypename ')'
	;
instrLdx:
	'ldx(' TokBuiltinTypename ')'
	;
instrSt:
	'st(' TokBuiltinTypename ')'
	;
instrStx:
	'stx(' TokBuiltinTypename ')'
	;
instrBinop:
	'binop(' TokBinOp ')'
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
TokBuiltinTypename: 
	('basic' | 'u32' | 's32' | 'u16' | 's16' | 'u8' | 's8')
	;
TokBinOp:
	( 'add' | 'sub' | 'mul' | 'sdiv' | 'udiv' | 'smod' | 'umod' 
	| 'bitand' | 'bitor' | 'bitxor' | 'bitlsl' | 'bitlsr' | 'bitasr' 
	| 'cmpeq' | 'cmpne' 
	| 'cmpult' | 'cmpslt' | 'cmpugt' | 'cmpsgt' 
	| 'cmpule' | 'cmpsle' | 'cmpuge' | 'cmpsge')
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
