#include "lexer_class.hpp"

namespace cake_plus_plus
{

void Token::eat_whitespace()
{
	while (has_curr_char() && isspace(curr_char()))
	{
		next_char();
	}
}


//Token Lexer::operator () (const SourceFileChunk& input_chunk) const
//{
//	Token ret(input_chunk);
//
//	_eat_whitespace(ret);
//
//	if (!ret.chunk().has_curr_char())
//	{
//		ret.set_tok(TokType::EndingWhitespace);
//		return ret;
//	}
//
//	auto chunk = ret.chunk();
//
//
//	// Keywords and idents
//	if (in_range_inclusive(chunk.curr_char(), 'A', 'Z')
//		|| in_range_inclusive(chunk.curr_char(), 'a', 'z')
//		|| (chunk.curr_char() == '_'))
//	{
//		std::string ident_str;
//
//		ident_str += chunk.next_char();
//
//		while (chunk.has_curr_char()
//			|| in_range_inclusive(chunk.curr_char(), 'A', 'Z')
//			|| in_range_inclusive(chunk.curr_char(), 'a', 'z')
//			|| in_range_inclusive(chunk.curr_char(), '0', '9')
//			|| (chunk.curr_char() == '_'))
//		{
//			ident_str += chunk.next_char();
//		}
//
//		// Handle keywords
//		if (ident_str == "auto")
//		{
//			ret.set_tok(TokType::MiscAuto);
//		}
//		else if (ident_str == "func")
//		{
//			ret.set_tok(TokType::MiscFunc);
//		}
//		else if (ident_str == "u8")
//		{
//			ret.set_tok(TokType::BuiltinTypeU8);
//		}
//		else if (ident_str == "s8")
//		{
//			ret.set_tok(TokType::BuiltinTypeS8);
//		}
//		else if (ident_str == "u16")
//		{
//			ret.set_tok(TokType::BuiltinTypeU16);
//		}
//		else if (ident_str == "s16")
//		{
//			ret.set_tok(TokType::BuiltinTypeS16);
//		}
//		else if (ident_str == "u32")
//		{
//			ret.set_tok(TokType::BuiltinTypeU32);
//		}
//		else if (ident_str == "s32")
//		{
//			ret.set_tok(TokType::BuiltinTypeS32);
//		}
//		else if (ident_str == "u64")
//		{
//			ret.set_tok(TokType::BuiltinTypeU64);
//		}
//		else if (ident_str == "s64")
//		{
//			ret.set_tok(TokType::BuiltinTypeS64);
//		}
//
//		// No keywords found... this is an identifier of some variety.
//		// Could be a custom type, could be a variable name....  At this
//		// stage, we don't know.
//		else
//		{
//			ret.set_tok(TokType::MiscIdent);
//		}
//
//		ret.set_str(unique_dup(ident_str));
//		ret.set_chunk(chunk);
//		return ret;
//	}
//
//
//	ret.set_tok(TokType::Bad);
//	return ret;
//}


} // end namespace cake_plus_plus
