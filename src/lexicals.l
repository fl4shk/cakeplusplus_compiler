digit		[0-9]
letter		[A-Za-z]
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
	extern const char* set_curr_var_name(char* some_var_name);
	extern void make_curr_var();
	extern void yyerror(char* msg);

%}

%%

[=+\-*/%()\[\]\{\}\n]		{
								return *yytext;
							}


[ \t]			; /* skip whitespace */


{ident}			{
					yylval.name = set_curr_var_name(yytext);
					make_curr_var();
					//printf("Here is an ident:  %s\n", yylval.name);
					return TokIdent;
				}
{dec_num}		{
					yylval.num = atoi(yytext);
					return TokDecNum;
				}

<<EOF>>			{
					return TokEof;
				}

.				{
					yyerror("Eek!");
				}

%%


int yywrap(void)
{
	return 1;
}
