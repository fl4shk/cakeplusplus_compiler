#ifndef allocation_stuff_hpp
#define allocation_stuff_hpp

#include "misc_includes.hpp"

extern "C"
{

const char* cstm_strdup(char* some_c_str);
const int* cstm_intdup(int num);

}

#endif		// allocation_stuff_hpp
