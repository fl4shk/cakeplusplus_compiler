%{
	#include <stdio.h>

	extern "C"
	{
	extern int yylex(void);
	void yyerror(char* msg);
	}
%}

%token TokIdent
%token TokDecNum
%token TokEof

%%

program:
	program expr '\n'		{ printf("%d\n", $2); }
	|
	;

expr:
	expr_add_sub								{ $$ = $1; }
	| expr '+' expr_add_sub						{ $$ = $1 + $3; }
	| expr '-' expr_add_sub						{ $$ = $1 - $3; }
	;

expr_add_sub:
	expr_mul_div_mod							{ $$ = $1; }
	| expr_add_sub '*' expr_mul_div_mod			{ $$ = $1 * $3; }
	| expr_add_sub '/' expr_mul_div_mod			{ $$ = $1 / $3; }
	| expr_add_sub '%' expr_mul_div_mod			{ $$ = $1 % $3; }
	;

expr_mul_div_mod:
	expr_dec_num								{ $$ = $1; }
	| '(' expr ')'								{ $$ = $2; }
	;

expr_dec_num:
	TokDecNum				{ $$ = $1; }
	;

%%

extern "C"
{
void yyerror(char* msg)
{
	fprintf(stderr, "%s\n", msg);
}
}