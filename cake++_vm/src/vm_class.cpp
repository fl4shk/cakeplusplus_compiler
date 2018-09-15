#include "vm_class.hpp"
#include <fstream>

namespace cakeplusplus
{

size_t Vm::InstrHeader::num_arg_bytes() const
{
	switch (group())
	{
		case 0:
			return 0;

		case 1:
			return 2;

		case 2:
			switch (oper())
			{
				case static_cast<decltype(oper())>
					(Vm::InstrGrp2Oper::Constu8):
				case static_cast<decltype(oper())>
					(Vm::InstrGrp2Oper::Consts8):
					return 1;

				case static_cast<decltype(oper())>
					(Vm::InstrGrp2Oper::Constu16):
				case static_cast<decltype(oper())>
					(Vm::InstrGrp2Oper::Consts16):
					return 2;

				case static_cast<decltype(oper())>
					(Vm::InstrGrp2Oper::Constu32):
				case static_cast<decltype(oper())>
					(Vm::InstrGrp2Oper::Consts32):
					return 4;

				case static_cast<decltype(oper())>
					(Vm::InstrGrp2Oper::Const):
					return 8;

				default:
					return 0;
			}

		case 3:
		case 4:
		default:
			return 0;
	}
}

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

u8 Vm::get_raw_mem8_at(Address where) const
{
	if (where < mem_amount())
	{
		return __mem[where];
	}
	else // if (where >= mem_amount)
	{
		printerr("Error:  get_raw_mem8_at():  address 0x", std::hex, where,
			std::dec, " not in allocated memory range!\n");
		exit(1);
	}
}
u16 Vm::get_raw_mem16_at(Address where) const
{
	u16 ret = 0;
	set_bits_with_range(ret, get_raw_mem8_at(where + 0), 15, 8);
	set_bits_with_range(ret, get_raw_mem8_at(where + 1), 7, 0);
	return ret;
}
u32 Vm::get_raw_mem32_at(Address where) const
{
	u32 ret = 0;
	set_bits_with_range(ret, get_raw_mem8_at(where + 0), 31, 24);
	set_bits_with_range(ret, get_raw_mem8_at(where + 1), 23, 16);
	set_bits_with_range(ret, get_raw_mem8_at(where + 2), 15, 8);
	set_bits_with_range(ret, get_raw_mem8_at(where + 3), 7, 0);
	return ret;
}
u64 Vm::get_mem64_at(Address where) const
{
	u64 ret = 0;
	set_bits_with_range(ret, get_raw_mem8_at(where + 0), 63, 56);
	set_bits_with_range(ret, get_raw_mem8_at(where + 1), 55, 48);
	set_bits_with_range(ret, get_raw_mem8_at(where + 2), 47, 40);
	set_bits_with_range(ret, get_raw_mem8_at(where + 3), 39, 32);
	set_bits_with_range(ret, get_raw_mem8_at(where + 4), 31, 24);
	set_bits_with_range(ret, get_raw_mem8_at(where + 5), 23, 16);
	set_bits_with_range(ret, get_raw_mem8_at(where + 6), 15, 8);
	set_bits_with_range(ret, get_raw_mem8_at(where + 7), 7, 0);
	return ret;
}

void Vm::set_mem8_at(Address where, u8 data)
{
	if (where < mem_amount())
	{
		__mem[where] = data;
	}
	else // if (where >= mem_amount)
	{
		printerr("Error:  set_mem8_at():  address 0x", std::hex, where,
			std::dec, " not in allocated memory range!\n");
		exit(1);
	}
}
void Vm::set_mem16_at(Address where, u16 data)
{
	set_mem8_at(where + 0, data >> 8);
	set_mem8_at(where + 1, data >> 0);
}
void Vm::set_mem32_at(Address where, u32 data)
{
	set_mem8_at(where + 0, data >> 24);
	set_mem8_at(where + 1, data >> 16);
	set_mem8_at(where + 2, data >> 8);
	set_mem8_at(where + 3, data >> 0);
}
void Vm::set_mem64_at(Address where, u64 data)
{
	set_mem8_at(where + 0, data >> 56);
	set_mem8_at(where + 1, data >> 48);
	set_mem8_at(where + 2, data >> 40);
	set_mem8_at(where + 3, data >> 32);
	set_mem8_at(where + 4, data >> 24);
	set_mem8_at(where + 5, data >> 16);
	set_mem8_at(where + 6, data >> 8);
	set_mem8_at(where + 7, data >> 0);
}

}
