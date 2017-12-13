grammar Grammar;

// Parser rules
program:
	statements
	;

statements:
	'{' listStatement '}'
	;

listStatement:
	statement
	| listStatement statement
	| // allow having nothing
	;

statement:
	statements
	| expr ';'
	| assignment ';'
	| ifStatement
	| ifChainStatement 
	| whileStatement 
	| doWhileStatement
	;

assignment:
	identExpr '=' expr
	;

ifStatement:
	TokIf '(' expr ')' statements
	;

ifChainStatement:
	TokIf '(' expr ')' statements TokElse elseStatements
	;


// Used so that if - else if - else chains can be formed correctly
elseStatements:
	ifChainStatement
	| statements
	;


whileStatement:
	TokWhile '(' expr ')' statements
	;

doWhileStatement:
	TokDo statements TokWhile '(' expr ')'
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
	/* identExpr
	| */ TokDecNum
	| '(' expr ')'
	;

identExpr:
	TokIdent
	;


// Lexer rules
TokIf: 'if' ;
TokElse: 'else' ;
TokWhile: 'while' ;
TokDo: 'do' ;
LexWhitespace: (' ' | '\t' | '\n') -> skip ;
TokOpLogical: ('&&' | '||') ;
TokOpCompare: ('==' | '!=' | '<' | '>' | '<=' | '>=') ;
TokOpAddSub: ('+' | '-') ;
TokOpMulDivMod: ('*' | '/' | '%') ;
TokOpBitwise: ('&' | '|' | '^' | '<<' | '>>' | '>>>') ;
TokDecNum: [0-9] ([0-9]*) ;
TokIdent: [A-Za-z_] (([A-Za-z_] | [0-9])*) ;