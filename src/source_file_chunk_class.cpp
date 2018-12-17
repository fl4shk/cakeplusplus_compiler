#include "source_file_chunk_class.hpp"

namespace cake_plus_plus
{

void SourceFileChunk::increment()
{
	++_total_pos;
	++_in_line_pos;

	if (curr_char() == '\n')
	{
		++_line_num;
		_in_line_pos = 0;
	}
}

void SourceFileChunk::add_to(size_t amount)
{
	for (size_t i=0; i<amount; ++i)
	{
		increment();
	}
}

void SourceFileChunk::_init_line_num_and_in_line_pos(size_t s_total_pos)
{
	_total_pos = 0;
	_line_num = 0;
	_in_line_pos = 0;

	add_to(s_total_pos);
}

} // end namespace cake_plus_plus
