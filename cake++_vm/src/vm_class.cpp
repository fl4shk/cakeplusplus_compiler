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
	//VmInstrOp op = VmInstrOp::constant;
	VmInstrOp op = get_op();

	while (op != VmInstrOp::quit)
	{
		exec_one_instr(op);
		op = get_op();
	}

	// return quit argument
	return pop();
}

void Vm::exec_one_instr(VmInstrOp op)
{
	switch (op)
	{
		case VmInstrOp::constant:
			push(get_imm_64());
			break;
		case VmInstrOp::constant_u32:
			push(get_imm_u32());
			break;
		case VmInstrOp::constant_s32:
			push(get_imm_s32());
			break;
		case VmInstrOp::constant_u16:
			push(get_imm_u16());
			break;
		case VmInstrOp::constant_s16:
			push(get_imm_s16());
			break;
		case VmInstrOp::constant_u8:
			push(get_imm_u8());
			break;
		case VmInstrOp::constant_s8:
			push(get_imm_s8());
			break;

		case VmInstrOp::arg:
			push(fp() - 8);
			break;
		case VmInstrOp::argx:
			push(fp() - 8 + pop());
			break;
		case VmInstrOp::var:
			push(fp() + 8);
			break;
		case VmInstrOp::varx:
			push(fp() + 8 + pop());
			break;
		case VmInstrOp::get_pc:
			push(pc());
			break;
		case VmInstrOp::jump:
			pc() = pop();
			break;

		case VmInstrOp::beq:
			{
				const auto offset = get_imm_64();
				const auto val = pop();

				if (val == 0)
				{
					pc() += offset;
				}
			}
			break;
		case VmInstrOp::bne:
			{
				const auto offset = get_imm_64();
				const auto val = pop();

				if (val != 0)
				{
					pc() += offset;
				}
			}
			break;
		case VmInstrOp::beq_near:
			{
				const auto offset = get_imm_s16();
				const auto val = pop();

				if (val == 0)
				{
					pc() += offset;
				}
			}
			break;
		case VmInstrOp::bne_near:
			{
				const auto offset = get_imm_s16();
				const auto val = pop();

				if (val != 0)
				{
					pc() += offset;
				}
			}
			break;

		case VmInstrOp::call:
			{
				const auto addr = pop();
				push(pc());
				const auto old_fp = fp();
				fp() = sp();
				push(old_fp);
				pc() = addr;
			}
			break;
		case VmInstrOp::ret:
			{
				const auto ret_addr = get_mem_64(fp());
				const auto old_fp = get_mem_64(fp() + 8);
				sp() = fp();
				fp() = old_fp;
				pc() = ret_addr;
			}
			break;

		case VmInstrOp::ld_basic:
			{
			}
			break;
		case VmInstrOp::ld_u32:
			{
			}
			break;
		case VmInstrOp::ld_s32:
			{
			}
			break;
		case VmInstrOp::ld_u16:
			{
			}
			break;
		case VmInstrOp::ld_s16:
			{
			}
			break;
		case VmInstrOp::ld_u8:
			{
			}
			break;
		case VmInstrOp::ld_s8:
			{
			}
			break;

		case VmInstrOp::ldx_basic:
			{
			}
			break;
		case VmInstrOp::ldx_u32:
			{
			}
			break;
		case VmInstrOp::ldx_s32:
			{
			}
			break;
		case VmInstrOp::ldx_u16:
			{
			}
			break;
		case VmInstrOp::ldx_s16:
			{
			}
			break;
		case VmInstrOp::ldx_u8:
			{
			}
			break;
		case VmInstrOp::ldx_s8:
			{
			}
			break;

		case VmInstrOp::st_basic:
			{
			}
			break;
		case VmInstrOp::st_u32:
			{
			}
			break;
		case VmInstrOp::st_s32:
			{
			}
			break;
		case VmInstrOp::st_u16:
			{
			}
			break;
		case VmInstrOp::st_s16:
			{
			}
			break;
		case VmInstrOp::st_u8:
			{
			}
			break;
		case VmInstrOp::st_s8:
			{
			}
			break;

		case VmInstrOp::stx_basic:
			{
			}
			break;
		case VmInstrOp::stx_u32:
			{
			}
			break;
		case VmInstrOp::stx_s32:
			{
			}
			break;
		case VmInstrOp::stx_u16:
			{
			}
			break;
		case VmInstrOp::stx_s16:
			{
			}
			break;
		case VmInstrOp::stx_u8:
			{
			}
			break;
		case VmInstrOp::stx_s8:
			{
			}
			break;


		case VmInstrOp::add_to_sp:
			{
			}
			break;

		case VmInstrOp::add:
			{
			}
			break;
		case VmInstrOp::sub:
			{
			}
			break;
		case VmInstrOp::mul:
			{
			}
			break;
		case VmInstrOp::sdiv:
			{
			}
			break;
		case VmInstrOp::udiv:
			{
			}
			break;
		case VmInstrOp::smod:
			{
			}
			break;
		case VmInstrOp::umod:
			{
			}
			break;

		case VmInstrOp::bit_and:
			{
			}
			break;
		case VmInstrOp::bit_or:
			{
			}
			break;
		case VmInstrOp::bit_xor:
			{
			}
			break;
		case VmInstrOp::bit_lsl:
			{
			}
			break;
		case VmInstrOp::bit_lsr:
			{
			}
			break;
		case VmInstrOp::bit_asr:
			{
			}
			break;


		case VmInstrOp::cmp_eq:
			{
			}
			break;
		case VmInstrOp::cmp_ne:
			{
			}
			break;
		case VmInstrOp::cmp_ult:
			{
			}
			break;
		case VmInstrOp::cmp_slt:
			{
			}
			break;
		case VmInstrOp::cmp_ugt:
			{
			}
			break;
		case VmInstrOp::cmp_sgt:
			{
			}
			break;
		case VmInstrOp::cmp_ule:
			{
			}
			break;
		case VmInstrOp::cmp_sle:
			{
			}
			break;
		case VmInstrOp::cmp_uge:
			{
			}
			break;
		case VmInstrOp::cmp_sge:
			{
			}
			break;


		case VmInstrOp::disp_num:
			{
			}
			break;
		case VmInstrOp::disp_num_unsigned:
			{
			}
			break;
		case VmInstrOp::disp_char:
			{
			}
			break;
		case VmInstrOp::disp_str:
			{
			}
			break;
		case VmInstrOp::get_num:
			{
			}
			break;

		case VmInstrOp::quit:
			err("exec_one_instr():  Eek!\n");
			break;
	}
}

VmInstrOp Vm::get_op()
{
	const VmInstrOp ret = static_cast<VmInstrOp>(get_mem_16(pc()));
	pc() += sizeof(VmInstrOp);
	return ret;
}

s64 Vm::get_imm_64()
{
	const s64 ret = get_mem_64(pc());
	pc() += sizeof(s64);
	return ret;
}
s64 Vm::get_imm_u32()
{
	const s64 ret = (s64)((u32)get_mem_32(pc()));
	pc() += sizeof(u32);
	return ret;
}
s64 Vm::get_imm_s32()
{
	const s64 ret = (s64)((s32)get_mem_32(pc()));
	pc() += sizeof(s32);
	return ret;
}
s64 Vm::get_imm_u16()
{
	const s64 ret = (s64)((u16)get_mem_16(pc()));
	pc() += sizeof(u16);
	return ret;
}
s64 Vm::get_imm_s16()
{
	const s64 ret = (s64)((s16)get_mem_16(pc()));
	pc() += sizeof(s16);
	return ret;
}
s64 Vm::get_imm_u8()
{
	const s64 ret = (s64)((u8)get_mem_8(pc()));
	pc() += sizeof(u8);
	return ret;
}
s64 Vm::get_imm_s8()
{
	const s64 ret = (s64)((s8)get_mem_8(pc()));
	pc() += sizeof(s8);
	return ret;
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

	////printout(sp(), " ", fp(), "\n");
	//for (size_t i=0; i<sp(); ++i)
	//{
	//	const u32 temp = get_mem_8(i);

	//	if (temp < 0x10)
	//	{
	//		printout(0);
	//	}
	//	printout(std::hex, temp, std::dec);
	//}


	// 16 because of space for return value and return address
	sp() += 16;

	// 8 because of space for return value
	fp() += 8;
}

s64 Vm::pop()
{
	if (sp() < 8)
	{
		err("pop():  Stack pointer out of valid range!");
	}

	sp() -= sizeof(s64);

	const s64 ret = get_mem_64(sp());
	return ret;
}
void Vm::push(s64 to_push)
{
	if ((sp() + 8) >= 0)
	{
		err("push():  Stack pointer out of valid range!");
	}
	
	set_mem_64(sp(), to_push);
	sp() += sizeof(s64);
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
