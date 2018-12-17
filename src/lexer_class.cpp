#include "lexer_class.hpp"

namespace cake_plus_plus
{

void Token::_eat_whitespace()
{
	while (_has_curr_char() && isspace(_curr_char()))
	{
		_next_char();
	}
}


void Lexer::operator () (Token& tok, SourceFileChunk& input_chunk) const
{
	tok._init(input_chunk);

	tok._eat_whitespace();

	if (!tok._has_curr_char())
	{
		tok.set_type(TokType::End);
		input_chunk.set_pos(tok.chunk().pos());
		return;
	}

	auto& chunk = tok.chunk();


	// Keywords and idents
	if (in_range_inclusive(tok._curr_char(), 'A', 'Z')
		|| in_range_inclusive(tok._curr_char(), 'a', 'z')
		|| (tok._curr_char() == '_'))
	{
		std::string ident_str;

		ident_str += tok._next_char();

		while (tok._has_curr_char()
			|| in_range_inclusive(tok._curr_char(), 'A', 'Z')
			|| in_range_inclusive(tok._curr_char(), 'a', 'z')
			|| in_range_inclusive(tok._curr_char(), '0', '9')
			|| (tok._curr_char() == '_'))
		{
			ident_str += tok._next_char();
		}

		// Handle keywords
		if (ident_str == "auto")
		{
			tok.set_type(TokType::MiscAuto);
		}
		else if (ident_str == "func")
		{
			tok.set_type(TokType::MiscFunc);
		}
		else if (ident_str == "u8")
		{
			tok.set_type(TokType::BuiltinTypeU8);
		}
		else if (ident_str == "s8")
		{
			tok.set_type(TokType::BuiltinTypeS8);
		}
		else if (ident_str == "u16")
		{
			tok.set_type(TokType::BuiltinTypeU16);
		}
		else if (ident_str == "s16")
		{
			tok.set_type(TokType::BuiltinTypeS16);
		}
		else if (ident_str == "u32")
		{
			tok.set_type(TokType::BuiltinTypeU32);
		}
		else if (ident_str == "s32")
		{
			tok.set_type(TokType::BuiltinTypeS32);
		}
		else if (ident_str == "u64")
		{
			tok.set_type(TokType::BuiltinTypeU64);
		}
		else if (ident_str == "s64")
		{
			tok.set_type(TokType::BuiltinTypeS64);
		}

		// No keywords found... this is an identifier of some variety.
		// Could be a custom type, could be a variable name....  At this
		// stage, we don't know.
		else
		{
			tok.set_type(TokType::MiscIdent);
		}

		tok.set_str(unique_dup(ident_str));
		input_chunk.set_pos(chunk.pos());
		return;
	}


	tok.set_type(TokType::Bad);
	input_chunk.set_pos(chunk.pos());
	return;
}


} // end namespace cake_plus_plus
