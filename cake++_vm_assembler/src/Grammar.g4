grammar Grammar;

// Parser rules
program:
	line*
	;

line:
	scopedLines
	| label (comment?) '\n'
	| instruction (comment?) '\n'
	//label '\n'
	//| instruction '\n'
	| comment '\n'
	| directive (comment?) '\n'
	| '\n'
	;

scopedLines:
	'{' (comment?) '\n'
	line*
	'}' (comment?) '\n'
	;

//label: TokIdent | TokKeywordIdent ':' ;
label: identName ':' ;


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


instrConst: 'const(' expr ')' ;

instrConstU32: 'const_u32(' expr ')' ;
instrConstS32: 'const_s32(' expr ')' ;
instrConstU16: 'const_u16(' expr ')' ;
instrConstS16: 'const_s16(' expr ')' ;
instrConstU8: 'const_u8(' expr ')' ;
instrConstS8: 'const_s8(' expr ')' ;

instrNoImmArgs: TokNoImmArgsOp ;

instrBeq: 'beq(' expr ')' ;
instrBne: 'bne(' expr ')' ;
instrBeqNear: 'beq_near(' expr ')' ;
instrBneNear: 'bne_near(' expr ')' ;
instrBinop: TokBinOp ;


comment: ';' (~ '\n')* ;
directive:
	dotSpaceDirective
	| dotDbDirective
	| dotDbU32Directive
	| dotDbS32Directive
	| dotDbU16Directive
	| dotDbS16Directive
	| dotDbU8Directive
	| dotDbS8Directive
	| dotCalliDirective
	| dotSyscalliDirective
	;

dotSpaceDirective: '.space' expr ;

dotDbDirective: '.db' ((expr ',')?) expr ;

dotDbU32Directive: '.db_u32' ((expr ',')?) expr ;
dotDbS32Directive: '.db_s32' ((expr ',')?) expr ;
dotDbU16Directive: '.db_u16' ((expr ',')?) expr ;
dotDbS16Directive: '.db_s16' ((expr ',')?) expr ;
dotDbU8Directive: '.db_u8' ((expr ',')?) expr ;
dotDbS8Directive: '.db_s8' ((expr ',')?) expr ;
dotCalliDirective: '.calli(' expr ')' ;
dotSyscalliDirective: '.syscalli(' expr ')' ;

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

exprBitInvert: '~' expr ;
exprNegate: '-' expr ;
exprLogNegate: '!' expr ;

identName: TokIdent | TokBinOp | TokNoImmArgsOp;

numExpr: TokDecNum | TokChar;

currPc: '.' ;



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


TokNoImmArgsOp: 
	('arg' | 'argx' | 'var' | 'varx'
	| 'get_pc' | 'jump'
	| 'call' | 'ret'
	| TokLdOp | TokLdxOp | TokStOp | TokStxOp
	| TokSyscallShorthandOp
	| 'add_to_sp'
	| 'syscall'
	| 'quit')
	;

TokBinOp:
	('add' | 'sub' | 'mul' 
	| 'udiv' | 'sdiv' | 'umod' | 'smod' 
	| 'bit_and' | 'bit_or' | 'bit_xor' 
	| 'bit_lsl' | 'bit_lsr' | 'bit_asr' 
	| 'cmp_eq' | 'cmp_ne' 
	| 'cmp_ult' | 'cmp_slt' | 'cmp_ugt' | 'cmp_sgt' 
	| 'cmp_ule' | 'cmp_sle' | 'cmp_uge' | 'cmp_sge')
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

TokSyscallShorthandOp:
	('disp_num' | 'disp_num_unsigned' | 'disp_char' | 'disp_str'
	| 'get_num');

fragment LexInsideChar: . ;
fragment LexCharDelim: '\'' ;
//fragment LexStrDelim: '\"' ;

TokChar: LexCharDelim LexInsideChar LexCharDelim ;
//TokStr: LexStrDelim (LexInsideChar*) LexStrDelim ;


TokOpLogical: ('&&' | '||') ;
TokOpCompare: ('==' | '!=' | '<' | '>' | '<=' | '>=') ;
TokOpAddSub: ('+' | '-') ;
TokOpMulDivMod: ('*' | '/' | '%') ;
TokOpBitwise: ('&' | '|' | '^' | '<<' | '>>' | '>>>') ;
TokDecNum: [0-9] ([0-9]*) ;

TokIdent: [A-Za-z_] (([A-Za-z_] | [0-9])*) ;
TokOther: . ;
