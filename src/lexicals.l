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
	#include "grammar.tab.hh"
	int yylex(void);
	//extern const char* set_curr_var_name(char* some_var_name);
	//extern void make_curr_var();
	//extern const char* make_curr_var(char* some_var_name);
	extern void yyerror(char* msg);
	extern const char* cstm_strdup(char* some_c_str);

%}

%%

{other_operator}	{
						return *yytext;
					}

"u8"|"u16"|"u32"|"u64"			{
									yylval.name = cstm_strdup(yytext);
									return TokBuiltinTypename;
								}
"s8"|"s16"|"s32"|"s64"			{
									yylval.name = cstm_strdup(yytext);
									return TokBuiltinTypename;
								}

"&&"|"||"						{
									yylval.name = cstm_strdup(yytext);
									return TokOpLogical;
								}
"&"|"|"|"^"|"<<"|">>"|">>>"		{
									yylval.name = cstm_strdup(yytext);
									return TokOpBitwise;
								}
"=="|"!="|"<"|">"|"<="|">="		{
									yylval.name = cstm_strdup(yytext);
									return TokOpCompare;
								}
"+"|"-"							{
									yylval.name = cstm_strdup(yytext);
									return TokOpAddSub;
								}
"*"|"/"|"%"						{
									yylval.name = cstm_strdup(yytext);
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
					yylval.name = cstm_strdup(yytext);
					return TokIdent;
				}
{dec_num}		{
					yylval.num = atoi(yytext);
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
