#include "lexer_class.hpp"

namespace cake_plus_plus
{

void Lexer::_eat_whitespace(Lexer::Result& result) const
{
	auto& chunk = result.chunk();

	while (chunk().has_curr_char()
		&& isspace(chunk().curr_char()))
	{
		chunk().increment();
	}
}


Lexer::Result Lexer::operator () (const SourceFileChunk& input_chunk) const
{
	Result ret(input_chunk);
	auto& chunk = ret.chunk();

	_eat_whitespace(ret);

	if (!chunk.has_curr_char())
	{
		ret.set_tok(Token::EndingWhitespace);
		return ret;
	}


	// Keywords and idents
	if (in_range_inclusive(chunk.curr_char(), 'A', 'Z')
		|| in_range_inclusive(chunk.curr_char(), 'a', 'z')
		|| (chunk.curr_char() == '_'))
	{
		std::string ident_str;

		ident_str += chunk.next_char();

		while (chunk.has_curr_char()
			|| in_range_inclusive(chunk.curr_char(), 'A', 'Z')
			|| in_range_inclusive(chunk.curr_char(), 'a', 'z')
			|| in_range_inclusive(chunk.curr_char(), '0', '9')
			|| (chunk.curr_char() == '_'))
		{
			ident_str += chunk.next_char();
		}

		// Handle keywords
		if (ident_str == "auto")
		{
			ret.set_tok(Token::MiscAuto);
		}
		else if (ident_str == "func")
		{
			ret.set_tok(Token::MiscFunc);
		}
		else if (ident_str == "u8")
		{
			ret.set_tok(Token::BuiltinTypeU8);
		}
		else if (ident_str == "s8")
		{
			ret.set_tok(Token::BuiltinTypeS8);
		}
		else if (ident_str == "u16")
		{
			ret.set_tok(Token::BuiltinTypeU16);
		}
		else if (ident_str == "s16")
		{
			ret.set_tok(Token::BuiltinTypeS16);
		}
		else if (ident_str == "u32")
		{
			ret.set_tok(Token::BuiltinTypeU32);
		}
		else if (ident_str == "s32")
		{
			ret.set_tok(Token::BuiltinTypeS32);
		}
		else if (ident_str == "u64")
		{
			ret.set_tok(Token::BuiltinTypeU64);
		}
		else if (ident_str == "s64")
		{
			ret.set_tok(Token::BuiltinTypeS64);
		}

		// No keywords found... this is an identifier of some variety.
		// Could be a custom type, could be a variable name....  At this
		// stage, we don't know.
		else
		{
			ret.set_tok(Token::MiscIdent);
		}

		ret.set_str(unique_dup(ident_str));
		return ret;
	}


	return ret;
}


} // end namespace cake_plus_plus
