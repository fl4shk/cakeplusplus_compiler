#ifndef src_source_file_chunk_class_hpp
#define src_source_file_chunk_class_hpp

// src/source_file_chunk_class.hpp

#include "misc_includes.hpp"
#include "alloc_stuff.hpp"

namespace cake_plus_plus
{

class Token;

class SourceFilePos2d
{
	friend class Token;

protected:		// variables
	size_t _line_num = 0, _pos_in_line = 0;

public:		// functions
	inline SourceFilePos2d(size_t s_line_num=0, size_t s_pos_in_line=0)
		: _line_num(s_line_num), _pos_in_line(s_pos_in_line)
	{
	}

	inline SourceFilePos2d(const SourceFilePos2d& to_copy) = default;

	virtual inline ~SourceFilePos2d()
	{
	}

	inline SourceFilePos2d& operator = (const SourceFilePos2d& to_copy)
		= default;

	inline void next(char c)
	{
		++_pos_in_line;

		if (c == '\n')
		{
			++_line_num;
			_pos_in_line = 0;
		}
	}

	GEN_GETTER_AND_SETTER_BY_VAL(line_num)
	GEN_GETTER_AND_SETTER_BY_VAL(pos_in_line)
};

class SourceFileChunk
{
	friend class Token;

protected:		// variables
	//ConstStrPtr _file_name = nullptr;
	ConstStrPtr _source_file_contents = nullptr;
	size_t _pos = 0;

public:		// functions

	inline SourceFileChunk(ConstStrPtr s_source_file_contents=nullptr,
		size_t s_pos=0)
		: _source_file_contents(s_source_file_contents), _pos(s_pos)
	{
	}

	inline SourceFileChunk(const SourceFileChunk& to_copy) = default;

	virtual inline ~SourceFileChunk()
	{
	}

	inline SourceFileChunk& operator = (const SourceFileChunk& to_copy)
		= default;

	inline auto curr_char() const
	{
		return source_file_contents()->at(pos());
	}
	inline bool has_curr_char() const
	{
		return (pos() < source_file_contents()->size());
	}
	inline auto next_char()
	{
		const auto ret = curr_char();
		++_pos;
		return ret;
	}

	void get_pos_2d(SourceFilePos2d& ret) const;

	GEN_GETTER_BY_VAL(source_file_contents)
	GEN_GETTER_BY_VAL(pos)
};

} // end namespace cake_plus_plus

#endif		// src_source_file_chunk_class_hpp
