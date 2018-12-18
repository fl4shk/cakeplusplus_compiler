grammar CompilerGrammar;

program:
	(listFunctions?)
	;

listFunctions:
	function
	(listFunctions?)
	;

function:
	TokIdent TokIdent '(' (listFunctionArgs?) ')'
	'{'
		(listStatements?)
	'}'

listFunctionArgs:
	functionArg
	(',' (listFunctionArgs?))
	;

listStatements:
	statement
	(listStatements?)
	;


functionArg:
	TokIdent TokIdent (('[' ']')*)
	;


statement:
	(stmtDeclVars ';')
	| (exprCall ';')
	| (stmtAssign ';')
	| stmtIf
	| stmtWhile
	| '{'
		(listStatements?)
	'}'
	;

stmtDeclVars:
	TokIdent identExpr
	((',' identExpr)*)
	;

stmtAssign:
	identExpr TokOpAssign expr
	;


stmtIf:
	'if' '(' expr ')'
	'{'
		(listStatements?)
	'}'
	(stmtElse?)
	;

stmtElse:
	'else'
	(stmtIf
	| '{'
		(listStatements?)
	'}')
	;

stmtWhile:
	'while' '(' expr ')'
	'{'
		(listStatements?)
	'}'
	;

// Expressions
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
	| exprCompare TokPlusMinus exprAddSub
	;

exprAddSub:
	exprMulDivModEtc
	| exprAddSub TokOpMulDivMod exprMulDivModEtc
	| exprAddSub TokOpBitwise exprMulDivModEtc
	;

exprMulDivModEtc:
	exprUnary
	| TokNum
	| identExpr
	| exprCall
	| '(' expr ')'
	;

exprUnary:
	exprBitInvert
	| exprNegate
	| exprLogNot
	;

exprCall:
	TokIdent '(' (listExpr?) ')'
	;

listExpr:
	expr
	(',' (listExpr?))
	;

identExpr:
	TokIdent (('[' expr ']')*)
	;
