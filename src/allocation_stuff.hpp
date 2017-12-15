#ifndef allocation_stuff_hpp
#define allocation_stuff_hpp

#include "misc_includes.hpp"

#include "symbol_table_classes.hpp"

#include <map>

int* cstm_intdup(int to_dup);
std::string* cstm_strdup(const std::string& to_dup);
VmCode* append_vm_code(Function& func);

#endif		// allocation_stuff_hpp
