#ifndef misc_bison_stuff_hpp
#define misc_bison_stuff_hpp


typedef union
{
	const int* num;
	const char* name;

	#ifdef __cplusplus
	AstNode* node;
	#else
	void* node;
	#endif

} YySType;

//#undef YYSTYPE
#define YYSTYPE YySType

//#define YY_DECL uintptr_t yylex(void)
//#define YY_DECL int yylex(void)

//#ifdef __cplusplus
//extern "C"
//{
//#endif		// __cplusplus
//
//extern YYSTYPE yylval;
//
//#ifdef __cplusplus
//}
//#endif		// __cplusplus

#endif		// misc_bison_stuff_hpp
