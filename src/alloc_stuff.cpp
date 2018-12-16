#include "alloc_stuff.hpp"

namespace cake_plus_plus
{

class AllocStuff
{
	friend StrPtr cstm_strdup(const std::string& to_dup);

private:		// variables
	static inline std::map<std::string, std::unique_ptr<const std::string>>
		_str_map;
};

StrPtr cstm_strdup(const std::string& to_dup)
{
	// This is NOT optimal, but it doesn't matter that much.
	if (AllocStuff::_str_map.count(to_dup) == 0)
	{
		std::unique_ptr<const std::string>
			to_insert(new const std::string(to_dup));
		AllocStuff::_str_map[to_dup] = std::move(to_insert);
	}
	return AllocStuff::_str_map.at(to_dup).get();
}

} // end namespace cake_plus_plus
