#include "misc_includes.hpp"
#include "vm_class.hpp"

int main(int argc, char** argv)
{
	if (argc != 3)
	{
		printerr("Usage:  ", argv[0], " mem_amount code_filename\n");
		exit(1);
	}

	cakeplusplus::Vm vm(convert_str_to<size_t>(argv[1]), argv[2]);

	return vm.run();
}
