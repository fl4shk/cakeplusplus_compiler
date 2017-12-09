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


%%

program:
	statements
		{
			ast.gen_program($1);
		}
	|
	;


statements:
	'{' list_statement '}'
		{
			$$ = ast.gen_statements(ast.gen_mkscope(), $2, 
				ast.gen_rmscope());
		}
	;

list_statement:
	{
		//printout("For the childrens.\n");
		$$ = ast.gen_list_statement();
	}
	| list_statement statement
		{
			//printout("Appending statement\n");
			$1->append_to_list($2);
			$$ = $1;
		}
	;

statement:
	statements
	{
		$$ = $1;
	}
	| TokIdent '=' expr ';'
		{
			$$ = ast.gen_assign($1, $3);
		}
	| TokIdent '[' expr ']' '=' expr ';'
		{
			$$ = ast.gen_indexed_assign($1, $3, $6);
		}
	| TokIf '(' expr ')' statement
		{
			$$ = ast.gen_if_statement($3, $5);
		}
	| TokIf '(' expr ')' statement TokElse statement
		{
			$$ = ast.gen_if_chain_statement($3, $5, $7);
		}
	| TokWhile '(' expr ')' statement
		{
			$$ = ast.gen_while_statement($3, $5);
		}
	| TokDo statement TokWhile '(' expr ')'
		{
			$$ = ast.gen_do_while_statement($2, $5);
		}
	| var_decl ';'
		{
			$$ = $1;
		}
	;

var_decl:
	var_decl_simple
		{
			$$ = $1;
		}
	| var_decl_array
		{
			$$ = $1;
		}
	;

var_decl_simple:
	TokBuiltinTypename TokIdent
		{
			$$ = ast.gen_var_decl_simple($1, $2);
		}
	;

var_decl_array:
	TokBuiltinTypename TokIdent '[' TokDecNum ']'
		{
			$$ = ast.gen_var_decl_array($1, $2, $4);
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
	| TokIdent '[' expr ']'
		{
			$$ = ast.gen_indexed_load($1, $3);
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

std::set<std::string> pool_for_cstm_strdup;

extern "C"
{
void yy_c_error(char* msg)
{
	fprintf(stderr, "%s\n", msg);
}
const char* cstm_strdup(char* some_c_str)
{
	//pool_for_cstm_strdup.push_back(std::string(some_c_str));

	pool_for_cstm_strdup.insert(std::string(some_c_str));

	//return pool_for_cstm_strdup.back().c_str();
	return pool_for_cstm_strdup.find(std::string(some_c_str))->c_str();
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
