#ifndef src_alloc_stuff_hpp
#define src_alloc_stuff_hpp

// src/alloc_stuff.hpp

#include "misc_includes.hpp"

namespace cake_plus_plus
{
// typedefs are used here to help ensure consistency... and to avoid the
// compiler spitting out an error if the "const" is ever forgotten.
typedef const std::string* ConstStrPtr;

ConstStrPtr ensure_unique(const std::string& to_dup);

} // end namespace cake_plus_plus


#endif		// src_alloc_stuff_hpp
