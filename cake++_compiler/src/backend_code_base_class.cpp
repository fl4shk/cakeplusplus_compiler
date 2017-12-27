#include "backend_code_base_class.hpp"

#include "backend_base_class.hpp"



std::ostream& BackendBase::osprint_code(std::ostream& os)
{
	__osprint_one_code(os, &__startup_code);

	for (auto iter : __func_vec)
	{
		osprintout(os, *iter->name(), ":\n");
		osprintout(os, "{\n");
		__osprint_one_code(os, __func_to_code_start_map.at(iter));
		osprintout(os, "}\n");
	}

	return os;
}
