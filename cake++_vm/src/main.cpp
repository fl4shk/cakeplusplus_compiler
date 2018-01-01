#include "vm_class.hpp"
#include <sstream>

int main(int argc, char** argv)
{
	if (argc != 3)
	{
		printerr("Usage:  ", argv[0], " input_filename memory_size\n");
		exit(1);
	}

	std::string input_fname;
	{
	std::stringstream sstm;
	sstm << argv[1];
	sstm >> input_fname;
	}

	size_t some_mem_size;

	{
	std::stringstream sstm;
	sstm << argv[2];
	sstm >> some_mem_size;
	}

	Vm vm(input_fname, some_mem_size);

	return vm.run();
}
