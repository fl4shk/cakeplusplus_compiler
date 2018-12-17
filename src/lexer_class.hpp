#ifndef src_lexer_class_hpp
#define src_lexer_class_hpp

// src/lexer_class.hpp

#include "misc_includes.hpp"
#include "alloc_stuff.hpp"

namespace cake_plus_plus
{

class Lexer
{
private:		// functions
	static inline const std::pair<ConstStrPtr, ConstStrPtr>
		_make_token_map_entry(const std::string& key,
		const std::string& value)
	{
		return std::pair<ConstStrPtr, ConstStrPtr>(unique_dup(key),
			unique_dup(value));
	}
public:		// constants
	static inline const std::map<ConstStrPtr, ConstStrPtr> TOKENS_MAP
	= {
		// Built-in Types
		_make_token_map_entry("u8", "BuiltinTypeU8"),
		_make_token_map_entry("s8", "BuiltinTypeS8"),
		_make_token_map_entry("u16", "BuiltinTypeU16"),
		_make_token_map_entry("s16", "BuiltinTypeS16"),
		_make_token_map_entry("u32", "BuiltinTypeU32"),
		_make_token_map_entry("s32", "BuiltinTypeS32"),
		_make_token_map_entry("u64", "BuiltinTypeU64"),
		_make_token_map_entry("s64", "BuiltinTypeS64"),

		//_make_token_map_entry("float32", "BuiltinTypeFloat32"),
		//_make_token_map_entry("float64", "BuiltinTypeFloat64"),


		//_make_token_map_entry("auto", "Auto"),

		_make_token_map_entry("func", "Func"),

		_make_token_map_entry("//", "LineComment"),

		// Arithmetic
		_make_token_map_entry("+", "OpPlus"),
		_make_token_map_entry("-", "OpMinus"),
		_make_token_map_entry("*", "OpAsterisk"),
		_make_token_map_entry("/", "OpDiv"),
		_make_token_map_entry("%", "OpModulo"),


		// Logical Unops
		_make_token_map_entry("!", "OpLogNot"),

		// Logical Binops
		_make_token_map_entry("&&", "OpLogAnd"),
		_make_token_map_entry("||", "OpLogOr"),


		// Bitwise Unops
		_make_token_map_entry("~", "OpBitNot"),

		// Bitwise Binops
		_make_token_map_entry("&", "OpBitAnd"),
		_make_token_map_entry("|", "OpBitOr"),
		_make_token_map_entry("^", "OpBitXor"),
		_make_token_map_entry("<<", "OpBitLsl"),
		_make_token_map_entry(">>", "OpBitLsr"),
		_make_token_map_entry(">>>", "OpBitAsr"),
	};

public:		// functions

};

} // end namespace cake_plus_plus

#endif		// src_lexer_class_hpp
