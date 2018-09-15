#include "vm_class.hpp"
#include <fstream>

namespace cakeplusplus
{

Vm::Vm(size_t s_mem_amount, const std::string& s_code_filename)
	: __mem_amount(s_mem_amount), __code_filename(s_code_filename)
{
	if (mem_amount() > max_mem_amount)
	{
		printerr("Error:  Too much memory requested.  Max amount ",
			"permitted:  ", max_mem_amount, "\n");
		exit(1);
	}

	__mem.reset(new u8[mem_amount()]);

	std::fstream code_file(code_filename(), (std::ios_base::in
		| std::ios_base::binary));

	size_t i = 0;
	do
	{
		if (i >= mem_amount())
		{
			printerr("Error:  Not enough memory requested for file \"",
				code_filename(), "\"!  Amount requested was ",
				mem_amount(), ".\n");
			exit(1);
		}

		const int c = code_file.get();
		__mem[i] = c;

		++i;

	} while (!code_file.eof());
}

Vm::~Vm()
{
}

int Vm::run()
{
	return 0;
}

}
