grammar CompilerGrammar;

// Parser rules
program:
	listFunctions
	;

listFunctions:
	function*
	;

function:
	MiscIdent MiscIdent
	PunctLParen listFunctionArgs PunctRParen
	PunctLBrace
		listStatements
	PunctRBrace
	;

listFunctionArgs:
	(functionArg ((PunctComma functionArg)*))?
	;

listStatements:
	statement*
	;


functionArg:
	MiscIdent MiscIdent ((PunctLBracket PunctRBracket)*)
	;


statement:
	(stmtDeclVars PunctSemicolon)
	| (exprCall PunctSemicolon)
	| (stmtAssign PunctSemicolon)
	| stmtIf
	| stmtWhile
	| scopedStatements
	;

scopedStatements:
	PunctLBrace
		listStatements
	PunctRBrace
	;

stmtDeclVars:
	MiscIdent identExpr
	((PunctComma identExpr)*)
	;

stmtAssign:
	identExpr OpAssign expr
	;


stmtIf:
	KwIf PunctLParen expr PunctRParen
	scopedStatements
	(stmtElse?)
	;

stmtElse:
	KwElse
	(stmtIf
	| scopedStatements)
	;

stmtWhile:
	KwWhile PunctLParen expr PunctRParen
	scopedStatements
	;

// Expressions
expr:
	exprLogical
	| expr OpLogical exprLogical
	;

exprLogical:
	exprCompare
	| exprLogical OpCompare exprCompare
	;

exprCompare:
	exprAddSub
	| exprCompare OpPlus exprAddSub
	| exprCompare OpMinus exprAddSub
	;

exprAddSub:
	exprMulDivModEtc
	| exprAddSub OpMulDivMod exprMulDivModEtc
	| exprAddSub OpBitwise exprMulDivModEtc
	;

exprMulDivModEtc:
	exprUnary
	| numExpr
	| identExpr
	| exprCall
	| PunctLParen expr PunctRParen
	;

exprUnary:
	exprBitNot
	| exprLogNot
	| exprNegate
	;

exprCall:
	MiscIdent PunctLParen (listExpr?) PunctRParen
	;

exprBitNot:
	OpBitNot expr
	;

exprLogNot:
	OpLogNot expr
	;

exprNegate:
	OpMinus expr
	;

listExpr:
	expr ((PunctComma expr)*)
	;

numExpr:
	NumDec
	| NumHex
	| NumBin
	;

identExpr:
	MiscIdent ((PunctLBrace expr PunctRBrace)*)
	;



// Lexer rules

LexWhitespace: (' ' | '\t' | '\n' ) -> skip ;
LexLineComment: ('//' | ';') (~ '\n')* -> skip ;

OpLogical: ('&&' | '||') ;
OpCompare: ('==' | '!=' | '<' | '>' | '<=' | '>=') ;
OpPlus: '+' ;
OpMinus: '-' ;
OpMulDivMod: ('*' | '/' | '%') ;
OpBitwise: ('&' | '|' | '^' | '<<' | '>>' | '>>>') ;
OpBitNot: '~' ;
OpLogNot: '!' ;
OpAssign: ('='
	| '+=' | '-=' | '*=' | '/=' | '%='
	| '&=' | '|=' | '^='
	| '<<=' | '>>=' | '>>>=')
	;



fragment FragMiscOneChar:
	~["\\\r\n]
	| FragMiscEscapeSequence
	| '\\\n' // Added line
	| '\\\r\n' // Added line
	;

fragment FragMiscEscapeSequence:
	'\\' ['"nrt\\]
	;

fragment FragMiscCharSequence:
	FragMiscOneChar+
	;

MiscStringLiteral:
	'"' (FragMiscCharSequence?) '"'
	;

NumDec: [0-9] ([0-9]*) ;
NumHex: '0x' ([0-9A-Fa-f]+) ;
NumBin: '0b' ([0-1]+) ;

// Keywords
KwIf: 'if' ;
KwElse: 'else' ;
KwWhile: 'while' ;
KwClass: 'class' ;


// Punctuation, etc.
PunctPeriod: '.' ;
PunctComma: ',' ;
PunctColon: ':' ;
PunctSemicolon: ';' ;
PunctLParen: '(' ;
PunctRParen: ')' ;
PunctLBracket: '[' ;
PunctRBracket: ']' ;
PunctLBrace: '{' ;
PunctRBrace: '}' ;


MiscIdent: [A-Za-z_] (([A-Za-z_] | [0-9])*) ;
MiscOther: . ;
