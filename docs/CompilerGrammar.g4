grammar CompilerGrammar;

program:
	(listFunctions*)
	;

listFunctions:
	function
	(listFunctions*)
	;

function:
	TokIdent TokIdent '(' (listFunctionArgs*) ')'
	'{'
		(listFunctionStatements*)
	'}'

listFunctionArgs:
	functionArg
	(',' listFunctionArgs*)
	;

listFunctionStatements:
	functionStatement
	(listFunctionStatements*)
	;


functionArg:
	TokIdent TokIdent
	;


functionStatement:
	(stmtDeclVars
	| stmtIf
	| stmtWhile
	| stmtCall
	| stmtAssign)
	';'
	;

stmtDeclVars:
	TokIdent TokIdent (('[' TokNum ']')*)
	;
