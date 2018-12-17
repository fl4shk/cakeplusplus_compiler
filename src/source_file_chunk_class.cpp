#include "source_file_chunk_class.hpp"

namespace cake_plus_plus
{

void SourceFileChunk::get_pos_2d(SourceFilePos2d& ret) const
{
	ret.set_line_num(0);
	ret.set_pos_in_line(0);

	for (size_t i=0; i<pos(); ++i)
	{
		ret.next(source_file_contents()->at(i));
	}
}

} // end namespace cake_plus_plus
