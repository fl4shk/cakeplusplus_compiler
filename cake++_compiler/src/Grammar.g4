grammar Grammar;

// Parser rules
program: funcDecl+ ;

funcDecl:
	builtinTypename 
	identName '(' ((funcArgDecl ',')* funcArgDecl)? ')'
	statements
	;

funcCall:
	identName '(' ((funcArgExpr ',')* funcArgExpr)? ')' 
	;


// Just so that there's a separate std::vector
funcArgExpr: identName ;


statements: '{' stmt* '}' ;

//comment: 
//	'/*' (~ '*/')*
//	| TokLineComment
//	;

stmt:
	statements
	| putnStatement ';'
	| varDecl ';'
	| funcCall ';'
	//| expr ';'
	////| exprMulDivModEtc ';'
	| assignment ';'
	| ifStatement
	| ifChainStatement
	| whileStatement
	| doWhileStatement
	//| forStatement
	| returnExprStatement ';'
	| returnNothingStatement ';'
	;


// Temporary pseudo-function
putnStatement: 'putn' '(' expr ')' ;


varDecl: builtinTypename (identDecl ',')* identDecl ;

funcArgDecl:
	builtinTypename identName
	| builtinTypename nonSizedArrayIdentName
	;

builtinTypename: TokBuiltinTypename ;


nonSizedArrayIdentName: identName '[' ']' ;
assignment: identLhs '=' expr ;

ifStatement: TokIf '(' expr ')' statements ;
ifChainStatement: TokIf '(' expr ')' statements TokElse elseStatements ;


// Used so that if - else if - else chains can be formed correctly
elseStatements:
	ifStatement
	| ifChainStatement
	| statements
	;


whileStatement: TokWhile '(' expr ')' statements ;
doWhileStatement: TokDo statements TokWhile '(' expr ')' ;
//forStatement: TokFor '(' stmt expr ';' expr ')' statements ;

returnExprStatement: TokReturn expr ;
returnNothingStatement: TokReturn ;

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
	| funcCall
	| identRhs
	| lenExpr
	| sizeofExpr
	| castExpr
	| '(' expr ')'
	;

exprUnary:
	exprBitInvert
	| exprNegate
	| exprLogNot
	;

exprBitInvert: '~' expr ;
exprNegate: '-' expr ;
exprLogNot: '!' expr ;

identLhs:
	identName
	| identName subscriptExpr
	;

identRhs:
	identName
	| identName subscriptExpr
	;

identDecl:
	identName
	| identName subscriptConst
	;

identName: TokIdent ;
numExpr: TokDecNum ;
lenExpr: 'len' '(' identName ')' ;
sizeofExpr: 'sizeof' '(' identName ')' ;
castExpr: TokBuiltinTypename '(' expr ')' ;
subscriptExpr: '[' expr ']' ;
subscriptConst: '[' numExpr ']' ;



// Lexer rules
TokIf: 'if' ;
TokElse: 'else' ;
TokWhile: 'while' ;
TokDo: 'do' ;
TokFor: 'for' ;
TokReturn: 'return' ;
LexLineComment: '//' (~ '\n')* -> skip;
LexMultilineComment: '/*' (.*?) '*/' -> skip ;
LexWhitespace: (' ' | '\t' | '\n') -> skip ;
TokOpLogical: ('&&' | '||') ;
TokOpCompare: ('==' | '!=' | '<' | '>' | '<=' | '>=') ;
TokOpAddSub: ('+' | '-') ;
TokOpMulDivMod: ('*' | '/' | '%') ;
//TokOpBitwise: ('&' | '|' | '^' | '<<' | '>>' | '>>>') ;
TokOpBitwise: ('&' | '|' | '^' | '<<' | '>>');
TokBuiltinTypename: 
	('u64' | 's64' | 'u32' | 's32' | 'u16' | 's16' | 'u8' | 's8')
	;
TokDecNum: [0-9] ([0-9]*) ;
TokIdent: [A-Za-z_] (([A-Za-z_] | [0-9])*) ;
