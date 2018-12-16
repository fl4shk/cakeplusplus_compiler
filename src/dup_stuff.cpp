#include "dup_stuff.hpp"

namespace cake_plus_plus
{

class DupStuff
{
	friend std::string* cstm_strdup(const std::string& to_dup);

private:		// variables
	static inline std::map<std::string, std::unique_ptr<std::string>>
		_str_map;
};

std::string* cstm_strdup(const std::string& to_dup)
{
	// This is NOT optimal, but it doesn't matter that much.
	if (DupStuff::_str_map.count(to_dup) == 0)
	{
		std::unique_ptr<std::string> to_insert(new std::string(to_dup));
		DupStuff::_str_map[to_dup] = std::move(to_insert);
	}
	return DupStuff::_str_map.at(to_dup).get();
}

} // end namespace cake_plus_plus
