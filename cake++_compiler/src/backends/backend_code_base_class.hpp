#ifndef backend_code_base_class_hpp
#define backend_code_base_class_hpp

#include "../misc_includes.hpp"
//#include "backend_base_class.hpp"

typedef std::string* Ident;

class BackendBase;

class BackendCodeBase
{
public:		// variables
	// Note that either lab_ident or func_ident may be used by the various
	// constant nodes
	// Label identifier:  used by branches, jumps, and fake_op_label
	Ident lab_ident = nullptr;

	// called Function identifier
	Ident func_ident = nullptr;


	// Circular linked list links
	BackendCodeBase * next, * prev;

public:		// functions
	BackendCodeBase()
	{
	}
	virtual ~BackendCodeBase()
	{
	}
};

#endif		// backend_code_base_class_hpp
