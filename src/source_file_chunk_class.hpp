#ifndef src_source_file_chunk_class_hpp
#define src_source_file_chunk_class_hpp

// src/source_file_chunk_class.hpp

#include "misc_includes.hpp"
#include "alloc_stuff.hpp"

namespace cake_plus_plus
{

class SourceFileChunk
{
protected:		// variables
	//ConstStrPtr _file_name = nullptr;
	ConstStrPtr _source_file_contents = nullptr;
	size_t _total_pos = 0, _line_num = 0, _in_line_pos = 0;

public:		// functions

	inline SourceFileChunk(ConstStrPtr s_source_file_contents=nullptr,
		size_t s_total_pos=0)
		: _source_file_contents(s_source_file_contents)
	{
		_init_line_num_and_in_line_pos(s_total_pos);
	}

	inline SourceFileChunk(const SourceFileChunk& to_copy) = default;

	virtual inline ~SourceFileChunk()
	{
	}

	inline SourceFileChunk& operator = (const SourceFileChunk& to_copy)
		= default;

	inline auto curr_char() const
	{
		return source_file_contents()->at(total_pos());
	}
	inline bool has_curr_char() const
	{
		return (total_pos() < source_file_contents()->size());
	}
	inline auto next_char()
	{
		const auto ret = curr_char();
		increment();
		return ret;
	}

	void increment();
	void add_to(size_t amount);

	GEN_GETTER_BY_VAL(source_file_contents)
	GEN_GETTER_BY_VAL(total_pos)
	GEN_GETTER_BY_VAL(line_num)
	GEN_GETTER_BY_VAL(in_line_pos)

protected:		// functions
	void _init_line_num_and_in_line_pos(size_t s_total_pos);
};

} // end namespace cake_plus_plus

#endif		// src_source_file_chunk_class_hpp
