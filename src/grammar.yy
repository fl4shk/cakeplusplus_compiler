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
	#include "../src/abstract_syntax_tree_class.hpp"
	#endif		// __cplusplus

	#define YYERROR_VERBOSE 1

	extern void yyerror(const char* msg);
	extern void yyerror(char* msg);
%}

%union
{
	int num;
	char* name;


	#ifdef __cplusplus
	AstNode* node;			// node of the abstract syntax tree
	#else
	void* node;
	#endif
}


%token <name> TokBuiltinTypename
%token <name> TokIdent
%token <num> TokDecNum
%token <name> TokOpLogical TokOpCompare TokOpAddSub 
%token <name> TokOpBitwise TokOpMulDivMod

%type <node> program statements list_statement statement
%type <node> expr expr_logical expr_compare
%type <node> expr_add_sub expr_mul_div_mod_etc


%%

program:
	statements
		{
			$$ = ast.gen_program($1);
		}
	;


statements:
	{
		$$ = ast.gen_statements(ast.gen_mkscope(), ast.gen_rmscope());
	}
	'{' list_statement '}'
		{
			$$->append_child($2);
		}
	;

list_statement:
	{
		$$ = ast.gen_list_statement();
	}
	list_statement statement
		{
			$$->append_to_list($2);
		}
	;

statement:
	statements
		{
			$$ = $1;
		}
	| TokIdent '=' expr ';'
		{
			ast.gen_assign($1, $3);
		}
	;


expr:
	expr_logical
		{
			$$ = $1;
		}
	| expr TokOpLogical expr_logical
		{
			$$ = ast.gen_binop($2, $1, $3);
		}
	;

expr_logical:
	expr_compare
		{
			$$ = $1;
		}
	| expr_logical TokOpCompare expr_compare
		{
			$$ = ast.gen_binop($2, $1, $3);
		}
	;

expr_compare:
	expr_add_sub
		{
			$$ = $1;
		}
	| expr_compare TokOpAddSub expr_add_sub
		{
			$$ = ast.gen_binop($2, $1, $3);
		}
	;

expr_add_sub:
	expr_mul_div_mod_etc
		{
			$$ = $1;
		}
	| expr_add_sub TokOpMulDivMod expr_mul_div_mod_etc
		{
			$$ = ast.gen_binop($2, $1, $3);
		}
	| expr_add_sub TokOpBitwise expr_mul_div_mod_etc
		{
			$$ = ast.gen_binop($2, $1, $3);
		}
	;

expr_mul_div_mod_etc:
	TokIdent
		{
			$$ = ast.gen_ident($1);
		}
	| TokDecNum
		{
			$$ = ast.gen_constant($1);
		}
	| '(' expr ')'
		{
			$$ = $2;
		}
	;


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
