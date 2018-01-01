grammar Grammar;

// Parser rules
//program: (classDecl | globalFuncDecl)+ ;
program: globalFuncDecl+;

//classDecl:
//	'class' identName
//	'{'
//		(memberVarDecl | memberFuncDecl)+
//	'}' ';'
//	;

globalFuncDecl: funcDecl ;
//memberFuncDecl: funcDecl ;

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
	| pseudoFuncCallStmt ';'
	| localVarDecl ';'
	| funcCall ';'
	//| expr ';'
	////| exprMulDivModEtc ';'
	| assignment ';'
	| extendedAssignment ';'
	| ifStatement
	| ifChainStatement
	| whileStatement
	| doWhileStatement
	//| forStatement
	| returnExprStatement ';'
	| returnNothingStatement ';'
	;


// Pseudo-functions (statements)
pseudoFuncCallStmt:
	putnStatement
	| putcharStatement
	;

putnStatement: 'putn' '(' expr ')' ;
putcharStatement: 'putchar' '(' expr ')' ;

// Pseudo-functions (expressions)
pseudoFuncCallExpr:
	getnExpr
	| getcharExpr
	;
getnExpr: 'getn()' ;
getcharExpr: 'getchar()' ;



//memberVarDecl: varDecl ;
localVarDecl: varDecl ;

varDecl: 
	builtinTypeVarDecl 
	//| classInstDecl
	; 

builtinTypeVarDecl: builtinTypename (identDecl ',')* identDecl ;
//classInstDecl: identName (identDecl ',')* identDecl ;

funcArgDecl:
	builtinTypename identName
	| builtinTypename nonSizedArrayIdentName
	;

builtinTypename: TokBuiltinTypename ;


nonSizedArrayIdentName: identName '[' ']' ;
assignment: identLhs '=' expr ;
extendedAssignment: identLhs TokOpExtendedAssignment expr ;

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
	//| exprCompare TokOpAddSub exprAddSub
	| exprJustAdd
	| exprJustSub
	;

exprJustAdd: exprAddSub '+' exprCompare ;
exprJustSub: exprAddSub '-' exprCompare ;

exprAddSub:
	exprMulDivModEtc
	| exprAddSub TokOpMulDivMod exprMulDivModEtc
	| exprAddSub TokOpBitwise exprMulDivModEtc
	;

exprMulDivModEtc:
	'~' exprBitInvert
	| '-' exprNegate
	| '!' exprLogNot

	| numExpr
	| funcCall
	| pseudoFuncCallExpr
	| identRhs
	| lenExpr
	| sizeofExpr
	| castExpr
	| ('(' expr ')')
	;


exprBitInvert: expr ;
exprNegate: expr ;
exprLogNot: expr ;

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
castExpr: builtinTypename '(' expr ')' ;
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
TokOpExtendedAssignment: 
	('+=' | '-=' | '*=' | '/=' | '%=' 
	| '&=' | '|=' | '^='
	| '<<=' | '>>=')
	;
TokOpLogical: ('&&' | '||') ;
TokOpCompare: ('==' | '!=' | '<' | '>' | '<=' | '>=') ;
//TokOpAddSub: ('+' | '-') ;
//TokOpAdd: '+' ;
//TokOpSub: '-' ;
TokOpMulDivMod: ('*' | '/' | '%') ;
TokOpBitInvert: '~' ;
//TokOpNegate: '-' ;
TokOpLogNot: '!' ;
//TokOpBitwise: ('&' | '|' | '^' | '<<' | '>>' | '>>>') ;
TokOpBitwise: ('&' | '|' | '^' | '<<' | '>>');
TokBuiltinTypename: 
	('u64' | 's64' | 'u32' | 's32' | 'u16' | 's16' | 'u8' | 's8')
	;
TokDecNum: [0-9] ([0-9]*) ;
TokIdent: [A-Za-z_] (([A-Za-z_] | [0-9])*) ;
