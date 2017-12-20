#ifndef allocation_stuff_hpp
#define allocation_stuff_hpp

#include "misc_includes.hpp"

//#include "symbol_table_classes.hpp"
#include "vm_code_class.hpp"

#include <map>

class VmCode;
class Function;

class AllocStuff
{
	friend int* cstm_intdup(int to_dup);
	friend std::string* cstm_strdup(const std::string& to_dup);
	friend VmCode* append_vm_code(Function& func);
	//friend AstNode* mk_ast_node();

private:			// static variables
	static std::map<int, std::unique_ptr<int>> __int_pool;
	static std::map<std::string, std::unique_ptr<std::string>>
		__str_pool;
	static std::vector<std::unique_ptr<VmCode>> __vm_code_pool;
	//static std::vector<std::unique_ptr<AstNode>> __ast_node_pool;

};

int* cstm_intdup(int to_dup);
std::string* cstm_strdup(const std::string& to_dup);

template<typename Type>
Type* append_vm_code(VmCode& some_vm_code) __attribute__((noinline));

template<typename Type>
Type* append_vm_code(VmCode& some_vm_code)
{
	auto& pool = AllocStuff::__vm_code_pool;

	std::unique_ptr<VmCode> p;
	p.reset(new Type());
	p->next = &some_vm_code;
	(p->prev = some_vm_code.prev)->next = p.get();
	some_vm_code.prev = p.get();

	pool.push_back(std::move(p));
	return pool.back().get();
}

#endif		// allocation_stuff_hpp
