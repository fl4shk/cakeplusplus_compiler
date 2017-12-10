#ifndef misc_bison_stuff_hpp
#define misc_bison_stuff_hpp


//union YySType
//{
//	const int* num;
//	const char* name;
//
//	#ifdef __cplusplus
//	AstNode* node;
//	#else
//	void* node;
//	#endif
//
//	#ifdef __cplusplus
//	inline YySType& operator = (AstNode* some_node)
//	{
//		node = some_node;
//		return *this;
//	}
//	inline operator AstNode* ()
//	{
//		return node;
//	}
//	inline void append_to_list(AstNode* to_append)
//	{
//		node->append_to_list(to_append);
//	}
//	#endif
//
//};

//#undef YYSTYPE
//#define YYSTYPE union YySType

//#define YY_DECL uintptr_t yylex(void)
//#define YY_DECL int yylex(void)

#ifdef __cplusplus
#define YYSTYPE AstNode*
#else
#define YYSTYPE void*
#endif		// __cplusplus


#ifdef __cplusplus
extern "C"
{
#endif		// __cplusplus

extern YYSTYPE ast_gen_builtin_typename(char* some_typename);
extern YYSTYPE ast_gen_ident(char* some_ident);
extern YYSTYPE ast_gen_constant(int some_num);
extern YYSTYPE ast_gen_initial_binop(char* some_op);

#ifdef __cplusplus
}
#endif		// __cplusplus

#endif		// misc_bison_stuff_hpp
