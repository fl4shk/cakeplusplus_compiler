grammar Grammar;

// Parser rules
program:
	funcDecl*
	;

funcDecl:
	's64' identName '(' ((varDecl ',')* varDecl)? ')' statements
	;

funcCall:
	identName '(' ((expr ',')* expr)? ')' 
	;


statements:
	'{' statement* '}'
	;

statement:
	statements
	| varDecl ';'
	| expr ';'
	| assignment ';'
	| ifStatement
	| ifChainStatement 
	| whileStatement 
	| doWhileStatement
	;

varDecl:
	's64' identDecl
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
	numExpr


	| funcCall
	| identExpr
	| '(' expr ')'
	//| '~' expr
	//| '-' expr
	//| '!' expr
	;


identExpr:
	identName
	| identName subscriptExpr
	;

identDecl:
	identName
	| identName subscriptConst
	;

identName:
	TokIdent
	;

numExpr:
	TokDecNum
	;

subscriptExpr:
	'[' expr ']'
	;

subscriptConst:
	'[' numExpr ']'
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
