%{
	#include <stdio.h>
	#ifdef __cplusplus
	#include "../src/misc_includes.hpp"
	#endif		// __cplusplus
	#include "../src/misc_int_types.h"

	#ifdef __cplusplus
	extern "C"
	{
	#endif		// __cplusplus

	extern int yylex(void);
	extern void yyerror(char* msg);

	#ifdef __cplusplus
	}
	#endif		// __cplusplus

	#ifdef __cplusplus
	#include "../src/symbol_table_extern_funcs.hpp"
	extern std::string assign_ident_str;
	#endif		// __cplusplus
%}

%union
{
	int num;
	const char* name;
}


%token <name> TokIdent
%token <num> TokDecNum
%token TokEof

%type <name> assign_ident
%type <name> ident
%type <num> expr
%type <num> expr_add_sub
%type <num> expr_mul_div_mod

%%

program:
	program statement '\n'
	| program statement TokEof		{ return 0; }
	|
	;

statement:
	expr							{ printf("%d\n", $1); }
	| assign_ident '=' expr		{
									//printout("Assignment:  ", 
									//	assign_ident_str, " = ", $3, "\n");
									set_var_val(assign_ident_str, $3);
								}
	| TokEof
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
	ident					{
								//printout("TokIdent:  ", $1, "\n");
								$$ = get_var_val($1);
							}
	| TokDecNum				{ $$ = $1; }
	| '(' expr ')'			{ $$ = $2; }
	;

ident:
	TokIdent				{
								//printout("ident thing:  ", $1, "\n");
								$$ = $1;
							}
	;

assign_ident:
	TokIdent				{
								//printout("assign_ident:  ", $1, "\n");
								$$ = $1;
								assign_ident_str = $1;
							}
%%

extern "C"
{
void yyerror(char* msg)
{
	fprintf(stderr, "%s\n", msg);
}
}

std::string assign_ident_str;
