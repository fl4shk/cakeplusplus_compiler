#include "allocation_stuff.hpp"
#include "symbol_table_classes.hpp"
//#include "abstract_syntax_tree_classes.hpp"


std::map<int, std::unique_ptr<int>> AllocStuff::__int_pool;
std::map<std::string, std::unique_ptr<std::string>> AllocStuff::__str_pool;
std::vector<std::unique_ptr<VmCode>> AllocStuff::__vm_code_pool;
std::vector<std::unique_ptr<RtlCode>> AllocStuff::__rtl_code_pool;
//std::vector<std::unique_ptr<AstNode>> AllocStuff::__ast_node_pool;

int* cstm_intdup(int to_dup)
{
	auto& pool = AllocStuff::__int_pool;

	if (pool.count(to_dup) == 0)
	{
		std::unique_ptr<int> to_insert;
		to_insert.reset(new int());
		*to_insert = to_dup;
		pool[to_dup] = std::move(to_insert);
	}

	return pool.at(to_dup).get();
}

std::string* cstm_strdup(const std::string& to_dup)
{
	auto& pool = AllocStuff::__str_pool;

	if (pool.count(to_dup) == 0)
	{
		std::unique_ptr<std::string> to_insert;
		to_insert.reset(new std::string());
		*to_insert = to_dup;
		pool[to_dup] = std::move(to_insert);
	}

	return pool.at(to_dup).get();
}

//VmCode* append_vm_code(VmCode& some_head)
//{
//	auto& pool = AllocStuff::__vm_code_pool;
//
//	std::unique_ptr<VmCode> p;
//	p.reset(new VmCode());
//	p->next = &some_head;
//	(p->prev = some_head.prev)->next = p.get();
//	some_head.prev = p.get();
//
//	pool.push_back(std::move(p));
//	return pool.back().get();
//}

//AstNode* mk_ast_node()
//{
//	auto& pool = AllocStuff::__ast_node_pool;
//
//	std::unique_ptr<AstNode> p;
//	p.reset(new AstNode());
//
//	pool.push_back(std::move(p));
//	return pool.back().get();
//}


//RtlCode* append_rtl_code(RtlCode& some_head)
//{
//	auto& pool = AllocStuff::__rtl_code_pool;
//
//	std::unique_ptr<RtlCode> p;
//	p.reset(new RtlCode());
//	p->next = &some_head;
//	(p->prev = some_head.prev)->next = p.get();
//	some_head.prev = p.get();
//
//	pool.push_back(std::move(p));
//	return pool.back().get();
//}

VmCode* mk_linked_vm_code(VmCode& some_head)
{
	auto p = mk_unlinked_vm_code();

	relink_vm_code(p, some_head.prev);

	return p;
}

VmCode* mk_linked_vm_code(VmCode& some_head, VmRawInstrOp s_raw_op)
{
	auto p = mk_unlinked_vm_code(s_raw_op);

	relink_vm_code(p, some_head.prev);

	return p;
}

VmCode* mk_unlinked_vm_code()
{
	auto& pool = AllocStuff::__vm_code_pool;

	std::unique_ptr<VmCode> p;
	p.reset(new VmCode());

	pool.push_back(std::move(p));
	return pool.back().get();
}

VmCode* mk_unlinked_vm_code(VmRawInstrOp s_raw_op)
{
	auto p = mk_unlinked_vm_code();
	p->raw_op = s_raw_op;

	switch (p->raw_op)
	{
		case VmRawInstrOp::constant_64:
			p->size += sizeof(u64);
			break;
		case VmRawInstrOp::constant_u32:
			p->size += sizeof(u32);
			break;
		case VmRawInstrOp::constant_s32:
			p->size += sizeof(s32);
			break;
		case VmRawInstrOp::constant_u16:
			p->size += sizeof(u16);
			break;
		case VmRawInstrOp::constant_s16:
			p->size += sizeof(s16);
			break;
		case VmRawInstrOp::constant_u8:
			p->size += sizeof(u8);
			break;
		case VmRawInstrOp::constant_s8:
			p->size += sizeof(s8);
			break;

		case VmRawInstrOp::arg:
			break;
		case VmRawInstrOp::argx:
			break;
		case VmRawInstrOp::var:
			break;
		case VmRawInstrOp::varx:
			break;
		case VmRawInstrOp::get_pc:
			break;
		case VmRawInstrOp::jump:
			break;

		case VmRawInstrOp::beq:
			p->size += sizeof(s64);
			break;
		case VmRawInstrOp::bne:
			p->size += sizeof(s64);
			break;
		case VmRawInstrOp::beq_near:
			p->size += sizeof(s16);
			break;
		case VmRawInstrOp::bne_near:
			p->size += sizeof(s16);
			break;

		case VmRawInstrOp::call:
			break;
		case VmRawInstrOp::ret:
			break;

		case VmRawInstrOp::ld_basic:
			break;
		case VmRawInstrOp::ld_u32:
			break;
		case VmRawInstrOp::ld_s32:
			break;
		case VmRawInstrOp::ld_u16:
			break;
		case VmRawInstrOp::ld_s16:
			break;
		case VmRawInstrOp::ld_u8:
			break;
		case VmRawInstrOp::ld_s8:
			break;

		case VmRawInstrOp::ldx_basic:
			break;
		case VmRawInstrOp::ldx_u32:
			break;
		case VmRawInstrOp::ldx_s32:
			break;
		case VmRawInstrOp::ldx_u16:
			break;
		case VmRawInstrOp::ldx_s16:
			break;
		case VmRawInstrOp::ldx_u8:
			break;
		case VmRawInstrOp::ldx_s8:
			break;

		case VmRawInstrOp::st_basic:
			break;
		case VmRawInstrOp::st_u32:
			break;
		case VmRawInstrOp::st_s32:
			break;
		case VmRawInstrOp::st_u16:
			break;
		case VmRawInstrOp::st_s16:
			break;
		case VmRawInstrOp::st_u8:
			break;
		case VmRawInstrOp::st_s8:
			break;

		case VmRawInstrOp::stx_basic:
			break;
		case VmRawInstrOp::stx_u32:
			break;
		case VmRawInstrOp::stx_s32:
			break;
		case VmRawInstrOp::stx_u16:
			break;
		case VmRawInstrOp::stx_s16:
			break;
		case VmRawInstrOp::stx_u8:
			break;
		case VmRawInstrOp::stx_s8:
			break;


		case VmRawInstrOp::add_to_sp:
			break;

		case VmRawInstrOp::add:
			break;
		case VmRawInstrOp::sub:
			break;
		case VmRawInstrOp::mul:
			break;
		case VmRawInstrOp::udiv:
			break;
		case VmRawInstrOp::sdiv:
			break;
		case VmRawInstrOp::umod:
			break;
		case VmRawInstrOp::smod:
			break;

		case VmRawInstrOp::bit_and:
			break;
		case VmRawInstrOp::bit_or:
			break;
		case VmRawInstrOp::bit_xor:
			break;
		case VmRawInstrOp::bit_lsl:
			break;
		case VmRawInstrOp::bit_lsr:
			break;
		case VmRawInstrOp::bit_asr:
			break;


		case VmRawInstrOp::cmp_eq:
			break;
		case VmRawInstrOp::cmp_ne:
			break;
		case VmRawInstrOp::cmp_ult:
			break;
		case VmRawInstrOp::cmp_slt:
			break;
		case VmRawInstrOp::cmp_ugt:
			break;
		case VmRawInstrOp::cmp_sgt:
			break;
		case VmRawInstrOp::cmp_ule:
			break;
		case VmRawInstrOp::cmp_sle:
			break;
		case VmRawInstrOp::cmp_uge:
			break;
		case VmRawInstrOp::cmp_sge:
			break;


		//disp_num,
		//disp_num_unsigned,
		//disp_char,
		//disp_str,
		//get_num,
		case VmRawInstrOp::syscall:
			break;

		case VmRawInstrOp::quit:
			break;


		// Labels have no size
		case VmRawInstrOp::fake_op_label:
			p->size = 0;
			break;

		default:
			printerr("mk_unlinked_vm_code():  Eek!\n");
			break;
	}

	return p;
}

RtlCode* mk_linked_rtl_code(Function& curr_func)
{
	auto p = mk_unlinked_rtl_code();

	relink_rtl_code(p, curr_func.rtl_code().prev);

	return p;
}
RtlCode* mk_linked_rtl_code(Function& curr_func, RtlInOp s_op)
{
	auto p = mk_unlinked_rtl_code(s_op);

	relink_rtl_code(p, curr_func.rtl_code().prev);

	return p;
}

RtlCode* mk_unlinked_rtl_code()
{
	auto& pool = AllocStuff::__rtl_code_pool;

	std::unique_ptr<RtlCode> p;
	p.reset(new RtlCode());

	pool.push_back(std::move(p));
	return pool.back().get();
}

RtlCode* mk_unlinked_rtl_code(RtlInOp s_op)
{
	auto p = mk_unlinked_rtl_code();
	p->set_op(s_op);
	return p;
}
