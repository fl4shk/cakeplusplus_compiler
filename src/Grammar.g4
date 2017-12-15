grammar Grammar;

// Parser rules
program:
	funcDecl+
	;

funcDecl:
	identName '(' ((funcVarDecl ',')* funcVarDecl)? ')' statements
	;

funcCall:
	identName '(' ((funcArgExpr ',')* funcArgExpr)? ')' 
	;


// Just so that there's a separate std::vector
// Also, variables must be used for function arguments.  They are passed
// by reference.
funcArgExpr:
	identName
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
	's64' (identDecl ',')* identDecl
	;

funcVarDecl:
	's64' identName
	| 's64' nonSizedArrayIdentName
	;


nonSizedArrayIdentName:
	identName '[' ']'
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
	| lenExpr
	| sizeofExpr
	| '(' expr ')'
	| TokOpUnary expr
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

lenExpr:
	'len' '(' identExpr ')'
	;

sizeofExpr:
	'sizeof' '(' identExpr ')'
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
TokOpUnary: ('~' | '-' | '!') ;
TokDecNum: [0-9] ([0-9]*) ;
TokIdent: [A-Za-z_] (([A-Za-z_] | [0-9])*) ;
