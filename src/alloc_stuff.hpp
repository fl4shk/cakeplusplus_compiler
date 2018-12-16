#ifndef src_alloc_stuff_hpp
#define src_alloc_stuff_hpp

// src/alloc_stuff.hpp

#include "misc_includes.hpp"

namespace cake_plus_plus
{
typedef const std::string* StrPtr;

StrPtr cstm_strdup(const std::string& to_dup);

} // end namespace cake_plus_plus


#endif		// src_alloc_stuff_hpp
