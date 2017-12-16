#include "vm_class.hpp"
#include <sstream>

int main(int argc, char** argv)
{
	if (argc != 2)
	{
		printerr("Usage:  ", argv[0], " memory_size\n");
		exit(1);
	}

	size_t some_mem_size;

	{
		std::stringstream sstm;
		sstm << argv[1];
		sstm >> some_mem_size;
	}

	Vm vm(some_mem_size);

	return vm.run();
}
