#include "allocation_stuff.hpp"
#include "symbol_table_classes.hpp"

class AllocStuff
{
	friend int* cstm_intdup(int to_dup);
	friend std::string* cstm_strdup(const std::string& to_dup);
	friend VmCode* append_vm_code(Function& func);

private:			// static variables
	static std::map<int, std::unique_ptr<int>> __int_pool;
	static std::map<std::string, std::unique_ptr<std::string>>
		__str_pool;
	static std::vector<std::unique_ptr<VmCode>> __vm_code_pool;

};

std::map<int, std::unique_ptr<int>> AllocStuff::__int_pool;
std::map<std::string, std::unique_ptr<std::string>> AllocStuff::__str_pool;
std::vector<std::unique_ptr<VmCode>> AllocStuff::__vm_code_pool;

int* cstm_intdup(int to_dup)
{
	auto& pool = AllocStuff::__int_pool;

	if (pool.count(to_dup) == 0)
	{
		std::unique_ptr<int> to_insert;
		to_insert.reset(new int());
		*to_insert = to_dup;
		pool[to_dup] = std::move(to_insert);
	}

	return pool.at(to_dup).get();
}

std::string* cstm_strdup(const std::string& to_dup)
{
	auto& pool = AllocStuff::__str_pool;

	if (pool.count(to_dup) == 0)
	{
		std::unique_ptr<std::string> to_insert;
		to_insert.reset(new std::string());
		*to_insert = to_dup;
		pool[to_dup] = std::move(to_insert);
	}

	return pool.at(to_dup).get();
}

VmCode* append_vm_code(Function& func)
{
	auto& pool = AllocStuff::__vm_code_pool;

	std::unique_ptr<VmCode> p;
	p.reset(new VmCode());
	p->next = &func.code();
	(p->prev = func.code().prev)->next = p.get();
	func.code().prev = p.get();

	pool.push_back(std::move(p));
	return pool.back().get();
}
