#ifndef misc_bison_stuff_hpp
#define misc_bison_stuff_hpp


union YySType
{
	const int* num;
	const char* name;

	#ifdef __cplusplus
	AstNode* node;
	#else
	void* node;
	#endif

	#ifdef __cplusplus
	inline YySType& operator = (AstNode* some_node)
	{
		node = some_node;
	}
	inline operator AstNode* ()
	{
		return node;
	}
	#endif

};

//#undef YYSTYPE
#define YYSTYPE union YySType

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
