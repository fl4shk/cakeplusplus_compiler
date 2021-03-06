#include "lexer_class.hpp"

namespace cake_plus_plus
{

void Token::_eat_whitespace_and_line_comments()
{
	bool done = false;

	while (!done)
	{
		done = true;

		// Eat whitespace
		while (_has_curr_char() && isspace(_curr_char()))
		{
			done = false;
			_go_to_next_char();
		}

		// Eat line comments
		if (_has_curr_char() && _has_next_char()
			&& (_curr_char() == '/') && (_next_char() == '/'))
		{
			done = false;
			_go_to_next_char();

			while (_has_curr_char() && (_curr_char() != '\n'))
			{
				_go_to_next_char();
			}

			if (!_has_curr_char())
			{
				done = true;
			}
		}
	}
}


void Lexer::run(Token& tok, SourceFileChunk& input_chunk)
{
	set_curr_tok(&tok);

	tok._init(input_chunk);

	// Om nom nom
	tok._eat_whitespace_and_line_comments();
	auto& chunk = tok.chunk();

	if (!has_curr_char())
	{
		tok.set_type(TokType::End);
		input_chunk.set_pos(chunk.pos());
		return;
	}


	std::string temp_str;

	// Shortcuts
	auto update_input_chunk_pos = [&]() -> void
	{
		input_chunk.set_pos(chunk.pos());
	};

	auto basic_lex = [&](char c, TokType tok_type) -> bool
	{
		if (curr_char() == c)
		{
			go_to_next_char();
			tok.set_type(tok_type);
			update_input_chunk_pos();
			return true;
		}
		return false;
	};

	auto one_or_two_lex = [&](char c_one, char c_two, TokType tok_type_one,
		TokType tok_type_two) -> bool
	{
		if (curr_char() == c_one)
		{
			go_to_next_char();

			if (has_curr_char() && (curr_char() == c_two))
			{
				go_to_next_char();
				tok.set_type(tok_type_two);
			}
			else
			{
				tok.set_type(tok_type_one);
			}

			update_input_chunk_pos();
			return true;
		}
		return false;
	};

	auto keyword_lex = [&](const std::string& s, TokType tok_type) -> bool
	{
		if (temp_str == s)
		{
			tok.set_str(unique_dup(temp_str));
			tok.set_type(tok_type);
			update_input_chunk_pos();
			return true;
		}
		return false;
	};



	// Constant strings
	if (curr_char() == '\"')
	{
		go_to_next_char();

		char c = '\0';

		bool bad = false;

		while (has_curr_char() && (!bad))
		{
			c = go_to_next_char();

			if (c == '\\')
			{
				c = go_to_next_char();

				switch (c)
				{
				case '"':
					temp_str += "\"";
					break;

				case 't':
					temp_str += "\t";
					break;

				case 'n':
					temp_str += "\n";
					break;

				case 'r':
					temp_str += "\r";
					break;

				case '\\':
					temp_str += "\\";
					break;

				default:
					bad = true;
					break;
				}
			}
			else if (c != '\"')
			{
				temp_str += c;
			}
			else
			{
				break;
			}
		}

		if ((c != '\"') || bad)
		{
			tok.set_type(TokType::InvalidBadStr);
		}
		else
		{
			tok.set_type(TokType::MiscStr);
		}

		update_input_chunk_pos();
		return;
	}

	// Keywords and idents
	if (in_range_inclusive(curr_char(), 'A', 'Z')
		|| in_range_inclusive(curr_char(), 'a', 'z')
		|| (curr_char() == '_'))
	{
		temp_str += go_to_next_char();

		while (has_curr_char()
			&& (in_range_inclusive(curr_char(), 'A', 'Z')
			|| in_range_inclusive(curr_char(), 'a', 'z')
			|| in_range_inclusive(curr_char(), '0', '9')
			|| (curr_char() == '_')))
		{
			temp_str += go_to_next_char();
		}


		if (keyword_lex("auto", TokType::KwAuto)
			|| keyword_lex("if", TokType::KwIf)
			|| keyword_lex("else", TokType::KwElse)
			|| keyword_lex("while", TokType::KwWhile))
		{
			return;
		}

		// No keywords found... this is an identifier of some variety.
		// Could be a custom type, could be a variable name....  At this
		// stage, we don't know.
		tok.set_type(TokType::MiscIdent);

		tok.set_str(unique_dup(temp_str));
		update_input_chunk_pos();
		return;
	}

	// Handle decimal numbers
	if (in_range_inclusive(curr_char(), '1', '9'))
	{
		temp_str += go_to_next_char();

		while (has_curr_char()
			&& in_range_inclusive(curr_char(), '0', '9'))
		{
			temp_str += go_to_next_char();
		}

		tok.set_num(0);
		for (auto iter : temp_str)
		{
			tok.set_num((tok.num() * 10) + (iter - '0'));
		}

		tok.set_type(TokType::MiscIntNum);
		update_input_chunk_pos();
		return;
	}

	// Handle 0, hexadecimal, and binary numbers
	if (curr_char() == '0')
	{
		go_to_next_char();

		tok.set_num(0);
		tok.set_type(TokType::MiscIntNum);

		if (!has_curr_char())
		{
			update_input_chunk_pos();
			return;
		}

		if (curr_char() == 'x')
		{
			go_to_next_char();

			bool found = false;

			while (has_curr_char()
				&& (in_range_inclusive(curr_char(), '0', '9')
				|| in_range_inclusive(curr_char(), 'a', 'f')
				|| in_range_inclusive(curr_char(), 'A', 'F')))
			{
				found = true;
				temp_str += go_to_next_char();
			}

			if (!found)
			{
				tok.set_type(TokType::InvalidBadHexNum);
			}
			else // if (found)
			{
				for (auto iter : temp_str)
				{
					if (in_range_inclusive(iter, '0', '9'))
					{
						tok.set_num((tok.num() * 16) + (iter - '0' + 0x0));
					}
					else if (in_range_inclusive(iter, 'a', 'f'))
					{
						tok.set_num((tok.num() * 16) + (iter - 'a' + 0xa));
					}
					else // if (in_range_inclusive(iter, 'A', 'F')
					{
						tok.set_num((tok.num() * 16) + (iter - 'A' + 0xA));
					}
				}
			}
			update_input_chunk_pos();
			return;
		}
		else if (curr_char() == 'b')
		{
			go_to_next_char();

			bool found = false;

			while (has_curr_char()
				&& in_range(curr_char(), '0', '1'))
			{
				found = true;
				temp_str += go_to_next_char();
			}

			if (!found)
			{
				tok.set_type(TokType::InvalidBadBinNum);
			}
			else // if (found)
			{
				for (auto iter : temp_str)
				{
					tok.set_num((tok.num() * 2) + (iter - '0' + 0b0));
				}
			}

			update_input_chunk_pos();
			return;
		}

		update_input_chunk_pos();
		return;
	}

	// Handle punctuation, operators, etc.

	if (basic_lex('(', TokType::PunctLParen)
		|| basic_lex(')', TokType::PunctRParen)
		|| basic_lex('[', TokType::PunctLBracket)
		|| basic_lex(']', TokType::PunctRBracket)
		|| basic_lex('{', TokType::PunctLBrace)
		|| basic_lex('}', TokType::PunctRBrace)
		|| basic_lex(';', TokType::PunctSemicolon)
		|| basic_lex(',', TokType::PunctComma)
		|| basic_lex('.', TokType::PunctPeriod)
		|| basic_lex('~', TokType::OpBitNot))
	{
		return;
	}

	if (one_or_two_lex('+', '=', TokType::OpPlus, TokType::AssignPlus)
		|| one_or_two_lex('-', '=', TokType::OpMinus,
			TokType::AssignMinus)
		|| one_or_two_lex('*', '=', TokType::OpMul, TokType::AssignMul)
		|| one_or_two_lex('/', '=', TokType::OpDiv, TokType::AssignDiv)
		|| one_or_two_lex('%', '=', TokType::OpModulo,
			TokType::AssignModulo)
		|| one_or_two_lex('!', '=', TokType::OpLogNot, TokType::CmpNe)
		|| one_or_two_lex('=', '=', TokType::AssignRegular,
			TokType::CmpEq)
		|| one_or_two_lex('^', '=', TokType::OpBitXor,
			TokType::AssignBitXor))
	{
		return;
	}

	if (curr_char() == '<')
	{
		go_to_next_char();

		// "<<" or "<<="
		if (has_curr_char() && (curr_char() == '<'))
		{
			go_to_next_char();

			if (has_curr_char() && (curr_char() == '='))
			{
				go_to_next_char();
				tok.set_type(TokType::AssignBitLsl);
			}
			else
			{
				tok.set_type(TokType::OpBitLsl);
			}
		}
		// "<="
		else if (has_curr_char() && (curr_char() == '='))
		{
			go_to_next_char();
			tok.set_type(TokType::CmpLe);
		}
		// "<"
		else
		{
			tok.set_type(TokType::CmpLt);
		}

		update_input_chunk_pos();
		return;
	}

	if (curr_char() == '>')
	{
		go_to_next_char();

		// ">>", ">>>", ">>=", or ">>>="
		if (has_curr_char() && (curr_char() == '>'))
		{
			go_to_next_char();

			// ">>>" or ">>>="
			if (has_curr_char() && (curr_char() == '>'))
			{
				go_to_next_char();

				// ">>>="
				if (has_curr_char() && (curr_char() == '='))
				{
					go_to_next_char();
					tok.set_type(TokType::AssignBitAsr);
				}
				// ">>>"
				else
				{
					tok.set_type(TokType::OpBitAsr);
				}
			}
			// ">>="
			else if (has_curr_char() && (curr_char() == '='))
			{
				go_to_next_char();
				tok.set_type(TokType::AssignBitLsr);
			}
			// ">>"
			else
			{
				tok.set_type(TokType::OpBitLsr);
			}
		}
		// ">="
		else if (has_curr_char() && (curr_char() == '='))
		{
			go_to_next_char();
			tok.set_type(TokType::CmpGe);
		}
		// ">"
		else
		{
			tok.set_type(TokType::CmpGt);
		}

		update_input_chunk_pos();
		return;
	}

	if (curr_char() == '&')
	{
		go_to_next_char();

		// "&&"
		if (has_curr_char() && (curr_char() == '&'))
		{
			go_to_next_char();
			tok.set_type(TokType::OpLogAnd);
		}

		// "&="
		else if (has_curr_char() == (curr_char() == '='))
		{
			go_to_next_char();
			tok.set_type(TokType::AssignBitAnd);
		}

		// "&"
		else
		{
			tok.set_type(TokType::OpBitAnd);
		}

		update_input_chunk_pos();
		return;
	}

	if (curr_char() == '|')
	{
		go_to_next_char();

		// "||"
		if (has_curr_char() || (curr_char() == '|'))
		{
			go_to_next_char();
			tok.set_type(TokType::OpLogOr);
		}

		// "|="
		else if (has_curr_char() == (curr_char() == '='))
		{
			go_to_next_char();
			tok.set_type(TokType::AssignBitOr);
		}

		// "|"
		else
		{
			tok.set_type(TokType::OpBitOr);
		}

		update_input_chunk_pos();
		return;
	}


	tok.set_type(TokType::InvalidNone);
	update_input_chunk_pos();
	return;
}


} // end namespace cake_plus_plus
