#include "allocation_stuff.hpp"

class IntDupStuff
{
	friend int* cstm_intdup(int to_dup);

private:			// static variables
	static std::map<int, std::unique_ptr<int>> __pool;

};

std::map<int, std::unique_ptr<int>> IntDupStuff::__pool;

int* cstm_intdup(int to_dup)
{
	auto& pool = IntDupStuff::__pool;

	if (pool.count(to_dup) == 0)
	{
		std::unique_ptr<int> to_insert;
		to_insert.reset(new int());
		*to_insert = to_dup;
		pool[to_dup] = std::move(to_insert);
	}

	return pool.at(to_dup).get();
}
