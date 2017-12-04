digit		[0-9]
letter		[A-Za-z]
operator		[=<>+\-*/%&|^()\[\]\{\};]

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

%}

%%

"u8"			{ return TokU8; }
"u16"			{ return TokU16; }
"u32"			{ return TokU32; }
"u64"			{ return TokU64; }
"s8"			{ return TokS8; }
"s16"			{ return TokS16; }
"s32"			{ return TokS32; }
"s64"			{ return TokS64; }
{operator}		{
					// Operators
					return *yytext;
				}
"<<"			{ return TokLsl; }
">>"			{ return TokLsr; }
">>>"			{ return TokAsr; }
"&&"			{ return TokLogicalAnd; }
"||"			{ return TokLogicalOr; }
"=="			{ return TokCmpEq; }
"!="			{ return TokCmpNe; }
"<="			{ return TokCmpLe; }
">="			{ return TokCmpGe; }



[ \t\n]			; // skip whitespace


{ident}			{
					//yylval.name = set_curr_var_name(yytext);
					//yylval.name = make_curr_var();
					yylval.name = yytext;
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
