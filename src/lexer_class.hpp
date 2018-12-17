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
		_make_token_map_entry("u8", "BuiltinTypeU8"),
		_make_token_map_entry("s8", "BuiltinTypeS8"),
		_make_token_map_entry("u16", "BuiltinTypeU16"),
		_make_token_map_entry("s16", "BuiltinTypeS16"),
		_make_token_map_entry("u32", "BuiltinTypeU32"),
		_make_token_map_entry("s32", "BuiltinTypeS32"),
		_make_token_map_entry("u64", "BuiltinTypeU64"),
		_make_token_map_entry("s64", "BuiltinTypeS64"),
	};

public:		// functions

};

} // end namespace cake_plus_plus

#endif		// src_lexer_class_hpp
