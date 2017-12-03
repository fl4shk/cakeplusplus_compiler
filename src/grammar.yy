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
	extern void yy_c_error(char* msg);

	#ifdef __cplusplus
	}
	#endif		// __cplusplus

	#ifdef __cplusplus
	#include "../src/symbol_table_class.hpp"
	#include "../src/ir_code_generator_class.hpp"
	extern std::string assign_ident_str;

	#endif		// __cplusplus

	#define YYERROR_VERBOSE 1

	extern void yyerror(const char* msg);
	extern void yyerror(char* msg);
%}

%union
{
	int num;
	const char* name;
	void* code;			// an index into the generated code
}


%token <name> TokIdent
%token <num> TokDecNum
%token TokLsl
%token TokLsr
%token TokAsr
%token TokLogicalAnd
%token TokLogicalOr
%token TokCmpEq
%token TokCmpNe
%token TokCmpLe
%token TokCmpGe

%type <name> assign_ident
%type <name> ident
%type <code> expr
%type <code> expr_logical
%type <code> expr_compare
%type <code> expr_add_sub
%type <code> expr_mul_div_mod_etc


%%

program:
	program pre_statement
	|
	;

pre_statement:
	pre_statement statement
	| statement
	;


statement:
	assign_ident '=' expr ';'
		{
			ircodegen.gen_store($3);
		}
	;

expr:
	expr_logical
		{
			$$ = $1;
		}
	| expr TokLogicalAnd expr_logical	
		{
			$$ = ircodegen.gen_logical_and($1, $3);
		}
	| expr TokLogicalOr expr_logical
		{
			$$ = ircodegen.gen_logical_or($1, $3);
		}
	;

expr_logical:
	expr_compare
		{
			$$ = $1;
		}
	| expr_logical TokCmpEq expr_compare
		{
			$$ = ircodegen.gen_cmp_eq($1, $3);
		}
	| expr_logical TokCmpNe expr_compare
		{
			$$ = ircodegen.gen_cmp_ne($1, $3);
		}
	| expr_logical '<' expr_compare
		{
			$$ = ircodegen.gen_cmp_lt($1, $3);
		}
	| expr_logical '>' expr_compare
		{
			$$ = ircodegen.gen_cmp_gt($1, $3);
		}
	| expr_logical TokCmpLe expr_compare
		{
			$$ = ircodegen.gen_cmp_le($1, $3);
		}
	| expr_logical TokCmpGe expr_compare
		{
			$$ = ircodegen.gen_cmp_ge($1, $3);
		}

expr_compare:
	expr_add_sub
		{
			$$ = $1;
		}
	| expr_compare '+' expr_add_sub
		{
			$$ = ircodegen.gen_add($1, $3);
		}
	| expr_compare '-' expr_add_sub
		{
			$$ = ircodegen.gen_sub($1, $3);
		}
	;

expr_add_sub:
	expr_mul_div_mod_etc
		{
			$$ = $1;
		}
	| expr_add_sub '*' expr_mul_div_mod_etc
		{
			$$ = ircodegen.gen_mul($1, $3);
		}
	| expr_add_sub '/' expr_mul_div_mod_etc
		{
			$$ = ircodegen.gen_div($1, $3);
		}
	| expr_add_sub '%' expr_mul_div_mod_etc
		{
			$$ = ircodegen.gen_mod($1, $3);
		}
	| expr_add_sub '&' expr_mul_div_mod_etc
		{
			$$ = ircodegen.gen_bitwise_and($1, $3);
		}
	| expr_add_sub '|' expr_mul_div_mod_etc
		{
			$$ = ircodegen.gen_bitwise_or($1, $3);
		}
	| expr_add_sub '^' expr_mul_div_mod_etc
		{
			$$ = ircodegen.gen_bitwise_xor($1, $3);
		}
	| expr_add_sub TokLsl expr_mul_div_mod_etc
		{
			$$ = ircodegen.gen_lsl($1, $3);
		}
	| expr_add_sub TokLsr expr_mul_div_mod_etc
		{
			$$ = ircodegen.gen_lsr($1, $3);
		}
	| expr_add_sub TokAsr expr_mul_div_mod_etc
		{
			$$ = ircodegen.gen_asr($1, $3);
		}
	;

expr_mul_div_mod_etc:
	ident
		{
			//printout("TokIdent:  ", $1, "\n");
			//$$ = get_var_val($1); 
			$$ = ircodegen.gen_load($1);
		}
	| TokDecNum
		{
			$$ = ircodegen.gen_constant($1);
		}
	| '(' expr ')'
		{
			$$ = $2;
		}
	;

ident:
	TokIdent
		{
			//printout("ident thing:  ", $1, "\n");
			$$ = $1;
		}
	;

assign_ident:
	TokIdent
	{
		//printout("assign_ident:  ", $1, "\n");
		//$$ = $1;
		assign_ident_str = $1;
	}

%%

extern "C"
{
void yy_c_error(char* msg)
{
	fprintf(stderr, "%s\n", msg);
}
}

void yyerror(const char* msg)
{
	fprintf(stderr, "%s\n", msg);
}

void yyerror(char* msg)
{
	fprintf(stderr, "%s\n", msg);
}

std::string assign_ident_str;
