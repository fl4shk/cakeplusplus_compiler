#ifndef allocation_stuff_hpp
#define allocation_stuff_hpp

#include "misc_includes.hpp"

//#include "symbol_table_classes.hpp"
#include "vm_code_class.hpp"
#include "ir_code_classes.hpp"

#include <map>

class VmCode;
class Function;

class AllocStuff
{
	friend int* cstm_intdup(int to_dup);
	friend std::string* cstm_strdup(const std::string& to_dup);
	//friend VmCode* append_vm_code(Function& func);
	//friend AstNode* mk_ast_node();
	friend VmCode* append_vm_code(VmCode& some_head);

	//friend IrCode* append_ir_code(IrCode& some_head);
	friend IrCode* mk_unlinked_ir_code();

private:			// static variables
	static std::map<int, std::unique_ptr<int>> __int_pool;
	static std::map<std::string, std::unique_ptr<std::string>>
		__str_pool;
	static std::vector<std::unique_ptr<VmCode>> __vm_code_pool;
	static std::vector<std::unique_ptr<IrCode>> __ir_code_pool;
	//static std::vector<std::unique_ptr<AstNode>> __ast_node_pool;

};

int* cstm_intdup(int to_dup);
std::string* cstm_strdup(const std::string& to_dup);
VmCode* append_vm_code(VmCode& some_head);
//IrCode* append_ir_code(IrCode& some_head);
IrCode* mk_unlinked_ir_code();
IrCode* mk_unlinked_ir_code(IrOp s_op);

#endif		// allocation_stuff_hpp
