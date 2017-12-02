#ifndef symbol_table_extern_funcs_hpp
#define symbol_table_extern_funcs_hpp

#include "misc_int_types.h"

extern void set_var_val(const std::string& some_var_name, s32 n_val);
extern s32 get_var_val(const std::string& some_var_name);
extern const std::string& get_curr_var_name();

#ifdef __cplusplus
extern "C"
{
#endif		// __cplusplus

extern const char* set_curr_var_name(char* some_var_name);
extern void make_curr_var();

#ifdef __cplusplus
}
#endif		// __cplusplus

#endif		// symbol_table_extern_funcs_hpp
