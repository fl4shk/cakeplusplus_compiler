#include "vm_class.hpp"

Vm::Vm(size_t s_mem_size)
{
	if (s_mem_size > max_mem_size)
	{
		printerr("Vm:  Error:  Too much memory to allocate!  ",
			"Note:  maximum allowed size is ", max_mem_size, "\n");
		exit(1);
	}
	else if (s_mem_size < min_mem_size)
	{
		printerr("Vm:  Error:  Too little memory to allocate!  ",
			"Note:  minimum allowed size is ", min_mem_size, "\n");
		exit(1);
	}

	__mem.resize(s_mem_size);

	__program = std::move(get_stdin_as_str());

	// Require even number of characters
	if ((__program.size() % 2) == 1)
	{
		printerr("Vm:  Error:  program file must consist of an even ",
			"number of characters!\n");
		exit(1);
	}

	// Max size of program is half the amount of allocated memory
	else if (__program.size() > __mem.size())
	{
		printerr("Vm:  Error:  program is too large!  ",
			"Note:  Maximum valid program size is always equal to ",
			"half the amount of allocated memory.  In this case, ",
			"the amount of allocated memory is ", __mem.size(), ".\n");
		exit(1);
	}

	pc() = 0;
	sp() = 0;
	fp() = 0;
	put_program_into_mem();
}

Vm::~Vm()
{
}

int Vm::run()
{
	return 9001;
}

void Vm::put_program_into_mem()
{
	//for (char c : __program)

	for (size_t i=0; i<__program.size(); i+=2)
	{
		u8 data = 0;;

		for (size_t j=i; j<i+2; ++j)
		{
			data <<= 4;
			const char c = __program.at(j);
			if ((c >= '0') && (c <= '9'))
			{
				data |= (c - '0') & 0xf;
			}
			else if ((c >= 'A') && (c <= 'F'))
			{
				data |= (c - 'A' + 10) & 0xf;
			}
			else if ((c >= 'a') && (c <= 'f'))
			{
				data |= (c - 'a' + 10) & 0xf;
			}
			else
			{
				printerr("Vm:  Error:  program file contains invalid ",
					"characters!\n");
				exit(1);
			}
		}

		set_mem_8(sp(), data);

		++sp();
		++fp();
	}

	//printout(sp(), " ", fp(), "\n");
	for (size_t i=0; i<sp(); ++i)
	{
		const u32 temp = get_mem_8(i);

		if (temp < 0x10)
		{
			printout(0);
		}
		printout(std::hex, temp, std::dec);
	}
}

u64 Vm::get_mem_64(size_t address) const
{
	if ((address >= __mem.size())
		|| ((address + 1) >= __mem.size())
		|| ((address + 2) >= __mem.size())
		|| ((address + 3) >= __mem.size())
		|| ((address + 4) >= __mem.size())
		|| ((address + 5) >= __mem.size())
		|| ((address + 6) >= __mem.size())
		|| ((address + 7) >= __mem.size()))
	{
		err(sconcat("Address ", address, " out of range for ",
			"64-bit read!"));
	}

	// Big endian
	u64 ret = 0;
	for (size_t i=address; i<address+sizeof(ret); ++i)
	{
		ret <<= 8;
		ret |= __mem.at(i);
	}

	return ret;

}
u64 Vm::set_mem_64(size_t address, u64 data)
{
	if ((address >= __mem.size())
		|| ((address + 1) >= __mem.size())
		|| ((address + 2) >= __mem.size())
		|| ((address + 3) >= __mem.size())
		|| ((address + 4) >= __mem.size())
		|| ((address + 5) >= __mem.size())
		|| ((address + 6) >= __mem.size())
		|| ((address + 7) >= __mem.size()))
	{
		err(sconcat("Address ", address, " out of range for ",
			"64-bit write!"));
	}

	// Big endian
	for (size_t i=address; i<address+8; ++i)
	{
		__mem.at(i) = (data >> (i * 8)) & 0xff;
	}

	return data;
}
u32 Vm::get_mem_32(size_t address) const
{
	if ((address >= __mem.size())
		|| ((address + 1) >= __mem.size())
		|| ((address + 2) >= __mem.size())
		|| ((address + 3) >= __mem.size()))
	{
		err(sconcat("Address ", address, " out of range for ",
			"32-bit read!"));
	}

	// Big endian
	u32 ret = 0;
	for (size_t i=address; i<address+sizeof(ret); ++i)
	{
		ret <<= 8;
		ret |= __mem.at(i);
	}

	return ret;
}
u32 Vm::set_mem_32(size_t address, u32 data)
{
	if ((address >= __mem.size())
		|| ((address + 1) >= __mem.size())
		|| ((address + 2) >= __mem.size())
		|| ((address + 3) >= __mem.size()))
	{
		err(sconcat("Address ", address, " out of range for ",
			"32-bit write!"));
	}

	// Big endian
	for (size_t i=address; i<address+4; ++i)
	{
		__mem.at(i) = (data >> (i * 8)) & 0xff;
	}

	return data;
}
u16 Vm::get_mem_16(size_t address) const
{
	if ((address >= __mem.size())
		|| ((address + 1) >= __mem.size()))
	{
		err(sconcat("Address ", address, " out of range for ",
			"16-bit read!"));
	}

	// Big endian
	u16 ret = 0;
	for (size_t i=address; i<address+sizeof(ret); ++i)
	{
		ret <<= 8;
		ret |= __mem.at(i);
	}

	return ret;
}
u16 Vm::set_mem_16(size_t address, u16 data)
{
	if ((address >= __mem.size())
		|| ((address + 1) >= __mem.size()))
	{
		err(sconcat("Address ", address, " out of range for ",
			"16-bit write!"));
	}

	// Big endian
	for (size_t i=address; i<address+2; ++i)
	{
		__mem.at(i) = (data >> (i * 8)) & 0xff;
	}

	return data;
}
u8 Vm::get_mem_8(size_t address) const
{
	if (address >= __mem.size())
	{
		err(sconcat("Address ", address, " out of range for ",
			"8-bit read!"));
	}

	u8 ret = __mem.at(address);
	return ret;
}
u8 Vm::set_mem_8(size_t address, u8 data)
{
	if (address >= __mem.size())
	{
		err(sconcat("Address ", address, " out of range for ",
			"8-bit write!"));
	}

	__mem.at(address) = data;

	return data;
}
