digit		[0-9]
letter		[A-Za-z]
__ident_non_start_char		{letter}|{digit}|[_]
__ident_start_char			{letter}|[_]
ident		{__ident_start_char}({__ident_non_start_char})*
num			{digit}({digit})*

%{
	typedef uint8_t u8;
	typedef uint16_t u16;
	typedef uint32_t u32;
	typedef uint64_t u64;
	typedef int8_t s8;
	typedef int16_t s16;
	typedef int32_t s32;
	typedef int64_t s64;
	extern u64 ident_count, num_count;

	extern int real_main(int argc, char** argv);
	extern void inc_ident_count();
	extern void inc_num_count();
%}

%%
	/* match identifier */
{ident}			inc_ident_count();
{num}			inc_num_count();

%%


int yywrap()
{
	return 1;
}

int main(int argc, char** argv)
{
	return real_main(argc, argv);
}
