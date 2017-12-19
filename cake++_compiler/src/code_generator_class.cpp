#include "code_generator_class.hpp"

CodeGenerator::CodeGenerator()
{
}

CodeGenerator::~CodeGenerator()
{
}

void CodeGenerator::generate(AstNode* prog_node)
{
	visit_prog(prog_node);
}

void CodeGenerator::__visit_child(AstNode* p)
{
	switch (p->op)
	{
		case AstOp::Prog:
			err("Programs should not be children nodes!");
			break;

		case AstOp::FuncDecl:
			//visit_func_decl(p);
			err("There is no visit function for FuncDecl!");
			break;

		//case AstOp::ClsDecl:
		//	visit_cls_decl(p);
		//	break;

		case AstOp::FuncArgDecl:
			visit_func_arg_decl(p);
			break;

		case AstOp::FuncArgExpr:
			visit_func_arg_expr(p);
			break;

		case AstOp::Stmt:
			visit_stmt(p);
			break;

		case AstOp::IdentDecl:
			visit_ident_decl(p);
			break;

		case AstOp::Expr:
			visit_expr(p);
			break;

		default:
			err("CodeGenerator::__visit_child():  Unkown node eek!");
			break;
	}
}

void CodeGenerator::visit_all_children(AstNode* p)
{
	for (auto iter : p->children)
	{
		__visit_child(iter);
	}
}

void CodeGenerator::visit_prog(AstNode* p)
{
	for (auto iter : p->children)
	{
		if (__func_tbl.contains(p->ident))
		{
			err(sconcat("cannot have more than one function called \"",
				*p->ident, "\"!"));
		}

		{
		Function to_insert_or_assign(p->ident);
		__func_tbl.insert_or_assign(std::move(to_insert_or_assign));
		}

		__curr_func = &__func_tbl.at(p->ident);

		// All the function childrens except the statements
		for (size_t i=0; i<iter->children.size()-1; ++i)
		{
			__visit_child(iter->children.at(i));
		}
	}

	//visit_all_children(p);

	for (auto iter : p->children)
	{
		__visit_func_decl_statements(iter);
	}
}
void CodeGenerator::__visit_func_decl_statements(AstNode* p)
{
	// Now handle the statements child
	sym_tbl().mkscope();

	__visit_child(p->children.back());

	// No real reason to remove the scope (?)
	sym_tbl().rmscope();

}
//void CodeGenerator::visit_cls_decl(AstNode* p)
//{
//}
void CodeGenerator::visit_func_arg_decl(AstNode* p)
{
}
void CodeGenerator::visit_func_arg_expr(AstNode* p)
{
}
void CodeGenerator::visit_stmt(AstNode* p)
{
}
void CodeGenerator::visit_ident_decl(AstNode* p)
{
}
void CodeGenerator::visit_expr(AstNode* p)
{
}


void CodeGenerator::visit_subop_bin(AstNode* p)
{
}
void CodeGenerator::visit_subop_un(AstNode* p)
{
}
