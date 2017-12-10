%{
	#include <stdio.h>

	#ifdef __cplusplus
	#include "../src/misc_includes.hpp"
	#endif		// __cplusplus

	#include "../src/misc_int_types.h"


	#ifdef __cplusplus
	#include "../src/symbol_table_class.hpp"
	#include "../src/abstract_syntax_tree_class.hpp"
	#endif		// __cplusplus

	#include "../src/misc_bison_stuff.hpp"



	#ifdef __cplusplus
	extern "C"
	{
	#endif		// __cplusplus

	//extern YY_DECL;
	extern int yylex(void);
	extern void yy_c_error(char* msg);

	#ifdef __cplusplus
	}
	#endif		// __cplusplus

	#define YYERROR_VERBOSE 1
	#define YYDEBUG 1

	extern void yyerror(const char* msg);
	extern void yyerror(char* msg);

%}


/*
%union
{
	const int* num;
	const char* name;


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
%token TokIf TokElse TokWhile TokDo

%type <node> expr expr_logical expr_compare
%type <node> expr_add_sub expr_mul_div_mod_etc
%type <node> statements list_statement statement
%type <node> var_decl var_decl_simple var_decl_array
*/

%token TokBuiltinTypename
%token TokIdent
%token TokDecNum
%token TokOpLogical TokOpCompare TokOpAddSub 
%token TokOpBitwise TokOpMulDivMod
%token TokIf TokElse TokWhile TokDo

%%

program:
	statements
		{
			ast.gen_program($1.node);
		}
	|
	;


statements:
	'{' list_statement '}'
		{
			$$.node = ast.gen_statements(ast.gen_mkscope(), $2.node, 
				ast.gen_rmscope());
		}
	;

list_statement:
	{
		//printout("For the childrens.\n");
		$$.node = ast.gen_list_statement();
	}
	| list_statement statement
		{
			//printout("Appending statement\n");
			$1.node->append_to_list($2.node);
			$$.node = $1.node;
		}
	;

statement:
	statements
	{
		$$.node = $1.node;
	}
	| TokIdent '=' expr ';'
		{
			$$.node = ast.gen_assign($1.name, $3.node);
		}
	| TokIdent '[' expr ']' '=' expr ';'
		{
			$$.node = ast.gen_indexed_assign($1.name, $3.node, $6.node);
		}
	| TokIf '(' expr ')' statement
		{
			$$.node = ast.gen_if_statement($3.node, $5.node);
		}
	| TokIf '(' expr ')' statement TokElse statement
		{
			$$.node = ast.gen_if_chain_statement($3.node, $5.node, 
				$7.node);
		}
	| TokWhile '(' expr ')' statement
		{
			$$.node = ast.gen_while_statement($3.node, $5.node);
		}
	| TokDo statement TokWhile '(' expr ')'
		{
			$$.node = ast.gen_do_while_statement($2.node, $5.node);
		}
	| var_decl ';'
		{
			$$.node = $1.node;
		}
	;

var_decl:
	var_decl_simple
		{
			$$.node = $1.node;
		}
	| var_decl_array
		{
			$$.node = $1.node;
		}
	;

var_decl_simple:
	TokBuiltinTypename TokIdent
		{
			printout("var_decl_simple:  ", 
				strappcom2($1.name, $2.name), "\n");
			$$.node = ast.gen_var_decl_simple($1.name, $2.name);
		}
	;

var_decl_array:
	TokBuiltinTypename TokIdent '[' TokDecNum ']'
		{
			$$.node = ast.gen_var_decl_array($1.name, $2.name, 
				$4.num);
		}
	;

expr:
	expr_logical
		{
			$$.node = $1.node;
		}
	| expr TokOpLogical expr_logical
		{
			$$.node = ast.gen_binop($2.name, $1.node, $3.node);
		}
	;

expr_logical:
	expr_compare
		{
			$$.node = $1.node;
		}
	| expr_logical TokOpCompare expr_compare
		{
			$$.node = ast.gen_binop($2.name, $1.node, $3.node);
		}
	;

expr_compare:
	expr_add_sub
		{
			$$.node = $1.node;
		}
	| expr_compare TokOpAddSub expr_add_sub
		{
			$$.node = ast.gen_binop($2.name, $1.node, $3.node);
		}
	;

expr_add_sub:
	expr_mul_div_mod_etc
		{
			$$.node = $1.node;
		}
	| expr_add_sub TokOpMulDivMod expr_mul_div_mod_etc
		{
			$$.node = ast.gen_binop($2.name, $1.node, $3.node);
		}
	| expr_add_sub TokOpBitwise expr_mul_div_mod_etc
		{
			$$.node = ast.gen_binop($2.name, $1.node, $3.node);
		}
	;

expr_mul_div_mod_etc:
	TokIdent
		{
			$$.node = ast.gen_ident($1.name);
		}
	| TokIdent '[' expr ']'
		{
			$$.node = ast.gen_indexed_load($1.name, $3.node);
		}
	| TokDecNum
		{
			$$.node = ast.gen_constant($1.num);
		}
	| '(' expr ')'
		{
			$$.node = $2.node;
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
