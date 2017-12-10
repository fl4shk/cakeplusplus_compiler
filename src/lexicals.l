digit		[0-9]
letter		[A-Za-z]
other_operator		[=()\[\]\{\};]

__ident_non_start_char		{letter}|{digit}|[_]
__ident_start_char			{letter}|[_]
ident		{__ident_start_char}({__ident_non_start_char})*
dec_num		{digit}({digit})*


%{
	/*
	typedef uint8_t u8; typedef int8_t s8;
	typedef uint16_t u16; typedef int16_t s16;
	typedef uint32_t u32; typedef int32_t s32;
	typedef uint64_t u64; typedef int64_t s64;
	*/





	#include <stdlib.h>
	#include "../src/misc_bison_stuff.hpp"
	#include "grammar.tab.hh"
	extern void yy_c_error(char* msg);


%}

%%

{other_operator}	{
						return *yytext;
					}

"u8"|"u16"|"u32"|"u64"			{
									//yylval = cstm_strdup(yytext);
									yylval = ast_gen_builtin_typename
										(yytext);
									return TokBuiltinTypename;
								}
"s8"|"s16"|"s32"|"s64"			{
									//yylval.name = cstm_strdup(yytext);
									yylval = ast_gen_builtin_typename
										(yytext);
									return TokBuiltinTypename;
								}

"&&"|"||"						{
									//yylval.name = cstm_strdup(yytext);
									yylval = ast_gen_initial_binop
										(yytext);
									return TokOpLogical;
								}
"&"|"|"|"^"|"<<"|">>"|">>>"		{
									//yylval.name = cstm_strdup(yytext);
									yylval = ast_gen_initial_binop
										(yytext);
									return TokOpBitwise;
								}
"=="|"!="|"<"|">"|"<="|">="		{
									//yylval.name = cstm_strdup(yytext);
									yylval = ast_gen_initial_binop
										(yytext);
									return TokOpCompare;
								}
"+"|"-"							{
									//yylval.name = cstm_strdup(yytext);
									yylval = ast_gen_initial_binop
										(yytext);
									return TokOpAddSub;
								}
"*"|"/"|"%"						{
									//yylval.name = cstm_strdup(yytext);
									yylval = ast_gen_initial_binop
										(yytext);
									return TokOpMulDivMod;
								}

"if"		{ return TokIf; }
"else"		{ return TokElse; }
"while"		{ return TokWhile; }
"do"		{ return TokDo; }



[ \t\n]			; // skip whitespace


{ident}			{
					//yylval.name = set_curr_var_name(yytext);
					//yylval.name = make_curr_var();
					//yylval.name = cstm_strdup(yytext);
					//printf("{ident}:  %s\n", (const char*)yylval);

					//printf("{ident}:  %i\n", strlen(yylval.name));

					yylval = ast_gen_ident(yytext);


					return TokIdent;
				}
{dec_num}		{
					//yylval.num = atoi(yytext);
					//yylval.num = cstm_intdup(atoi(yytext));

					yylval = ast_gen_constant(atoi(yytext));
					return TokDecNum;
				}



<<EOF>>			{
					return EOF;
				}

.				{
					yy_c_error("Lexer Eek!");
				}

%%


int yywrap(void)
{
	return 1;
}
