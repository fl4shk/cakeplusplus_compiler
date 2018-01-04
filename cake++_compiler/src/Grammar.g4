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
	| doWhileStatement ';'
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

//anyTypename: 
//	identName
//	| builtinTypename ;
builtinTypename: TokBuiltinTypename ;

//fullTypename: anyTypename (ptrSpecifier*) ;
//
//ptrSpecifier: '$';

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
	//| expr TokOpLogical exprLogical
	//| exprJustLogAnd | exprJustLogOr
	| expr exprFinishLogAnd exprLogical
	| expr exprFinishLogOr exprLogical
	;

exprFinishLogAnd: '&&' ;
exprFinishLogOr: '||' ;

// TokOpLogical: ('&&' | '||') ;

exprLogical:
	exprCompare
	//| exprLogical TokOpCompare exprCompare
	//| exprJustCompareEq | exprJustCompareNe
	//| exprJustCompareLt | exprJustCompareGt
	//| exprJustCompareLe | exprJustCompareGe

	| exprLogical exprFinishCompareEq exprCompare
	| exprLogical exprFinishCompareNe exprCompare
	| exprLogical exprFinishCompareLt exprCompare
	| exprLogical exprFinishCompareGt exprCompare
	| exprLogical exprFinishCompareLe exprCompare
	| exprLogical exprFinishCompareGe exprCompare
	;

// TokOpCompare: ('==' | '!=' | '<' | '>' | '<=' | '>=') ;

exprFinishCompareEq: '==' ;
exprFinishCompareNe: '!=' ;
exprFinishCompareLt: '<' ;
exprFinishCompareGt: '>' ;
exprFinishCompareLe: '<=' ;
exprFinishCompareGe: '>=' ;

exprCompare:
	exprAddSub
	| exprCompare exprFinishAdd exprAddSub
	| exprCompare exprFinishSub exprAddSub
	;

exprFinishAdd: '+' ;
exprFinishSub: '-' ;

exprAddSub:
	exprMulDivModEtc
	//| exprJustMul | exprJustDiv | exprJustMod
	//| exprJustBitAnd | exprJustBitOr | exprJustBitXor
	//| exprJustBitShiftLeft | exprJustBitShiftRight
	| exprAddSub exprFinishMul exprMulDivModEtc
	| exprAddSub exprFinishDiv exprMulDivModEtc
	| exprAddSub exprFinishMod exprMulDivModEtc
	| exprAddSub exprFinishBitAnd exprMulDivModEtc
	| exprAddSub exprFinishBitOr exprMulDivModEtc
	| exprAddSub exprFinishBitXor exprMulDivModEtc
	| exprAddSub exprFinishBitShiftLeft exprMulDivModEtc
	| exprAddSub exprFinishBitShiftRight exprMulDivModEtc
	;

exprFinishMul: '*' ;
exprFinishDiv: '/' ;
exprFinishMod: '%' ;
exprFinishBitAnd: '&' ;
exprFinishBitOr: '|' ;
exprFinishBitXor: '^' ;
exprFinishBitShiftLeft: '<<' ;
exprFinishBitShiftRight: '>>' ;

exprMulDivModEtc:
	exprBitInvert
	| exprNegate
	| exprLogNot

	| numExpr
	| funcCall
	| pseudoFuncCallExpr
	| identRhs
	| lenExpr
	| sizeofExpr
	| castExpr
	| '(' expr ')'
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
TokBuiltinTypename: 
	('u64' | 's64' | 'u32' | 's32' | 'u16' | 's16' | 'u8' | 's8')
	;
TokDecNum: [0-9] ([0-9]*) ;
TokIdent: [A-Za-z_] (([A-Za-z_] | [0-9])*) ;
