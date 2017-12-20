#ifndef symbol_table_base_class_hpp
#define symbol_table_base_class_hpp


#include "misc_includes.hpp"
#include "ident_table_classes.hpp"



// This is kind of like a stack

// This class exists because I realized I needed to keep symbols around
// even after they go out of scope.  This is useful for both optimization
// purposes (re-use old local variable space, for example) and also... to
// guarantee correct code generation, lol.
template<typename Type>
class SymbolTableBase
{
public:		// typedefs and constants
	typedef IdentTable<Type> OneTable;
	//typedef int OneTable;

	static constexpr s64 builtin_scope_level = 0;
	static constexpr s64 not_found_level = builtin_scope_level - 1;

public:		// classes
	class Node
	{
	public:		// variables
		OneTable table;

		Node* parent;
		std::vector<Node*> children;


	public:		// functions
		inline Node(Node* s_parent=nullptr)
			: parent(s_parent)
		{
		}

		inline void append_child(Node* to_append)
		{
			children.push_back(to_append);
		}

		//void print(size_t num_tabs=0)
		//{
		//	for (size_t i=0; i<num_tabs; ++i)
		//	{
		//		printout("\t");
		//	}
		//	printout(table, "\n");

		//	for (auto child : children)
		//	{
		//		child->print(num_tabs + 1);
		//	}
		//}
	};


protected:		// variables
	Node __tree;

	//Node* __curr_node = &__tree;
	Node* __curr_node = nullptr;


	// The number of scopes that have been made - 1
	s64 __scope_num = -1;

	//s64 __scope_lev = -1;

	std::vector<Node*> __node_pool;

public:		// functions
	inline SymbolTableBase()
	{
		//table.push_back(std::vector<OneTable>());
		__curr_node = &__tree;
		mkscope();
	}
	virtual ~SymbolTableBase()
	{
		for (size_t i=0; i<__node_pool.size(); ++i)
		{
			delete __node_pool.at(i);
		}
	}

	void mkscope() __attribute__((noinline))
	{
		////table().back().push_back(OneLevelTable());
		//++__scope_lev;

		////if (table().at(scope_lev()).size() == 0)
		//if (table().size() <= (u64)scope_lev())
		//{
		//	table().push_back(std::vector<OneTable>());
		//}

		//table().at(scope_lev()).push_back(OneTable());
		//table().at(scope_lev()).back() = __scope_num;

		++__scope_num;

		if (scope_num() < 0)
		{
			printerr("SymbolTableBase::mkscope():  ",
				"Far, FAR too many scopes!\n");
			exit(1);
		}

		__node_pool.push_back(new Node(__curr_node));

		__curr_node->append_child(__node_pool.back());
		auto old_curr_node = __curr_node;
		__curr_node = __curr_node->children.back();
		__curr_node->parent = old_curr_node;

		//__curr_node->table = scope_num();
	}
	void rmscope() __attribute__((noinline))
	{
		//if (scope_lev() > builtin_scope_level)
		//{
		//	//table().pop_back();
		//	--__scope_lev;
		//}
		//else
		//{
		//	printerr("SymbolTableBase::rmscope():  Eek!\n");
		//	exit(1);
		//}
		if (__curr_node != &__tree)
		{
			__curr_node = __curr_node->parent;
		}
		else
		{
			printerr("SymbolTableBase::rmscope():  Eek!\n");
			exit(1);
		}
	}

	inline void insert_or_assign(const Type& to_insert_or_assign)
	{
		__curr_node->table.insert_or_assign(to_insert_or_assign);
	}
	inline void insert_or_assign(Type&& to_insert_or_assign)
	{
		__curr_node->table.insert_or_assign
			(std::move(to_insert_or_assign));
	}


	Type* find(Ident some_name) __attribute__((noinline))
	{
		//for (s64 i=scope_lev(); i>=builtin_scope_level; --i)
		for (auto p=__curr_node; p!=&__tree; p=p->parent)
		{
			//if (table().at(i).contains(some_name))
			//{
			//	return &table().at(i).at(some_name);
			//}
			if (p->table.contains(some_name))
			{
				return &p->table.at(some_name);
			}
		}

		return nullptr;
	}

	inline Type* find_in_first_blklev(Ident some_name)
	{
		if (__tree.children.size() == 0)
		{
			return nullptr;
		}



		if (__tree.children.front()->table.contains(some_name))
		{
			return &__tree.children.front()->table.at(some_name);
		}

		return nullptr;
	}

	inline Type* find_in_this_blklev(Ident some_name)
	{
		//if (table.at(scope_lev()).back().contains(some_name))
		//{
		//	return &table.at(scope_lev()).back().at(some_name);
		//}

		if (__curr_node->table.contains(some_name))
		{
			return &__curr_node->table.at(some_name);
		}

		return nullptr;
	}

	inline Type* find_or_insert(Ident some_name)
	{
		{
			auto search = find(some_name);

			if (search != nullptr)
			{
				return search;
			}
		}

		Type to_insert;
		to_insert.set_name(some_name);
		insert_or_assign(std::move(to_insert));

		return find(some_name);
	}

	gen_getter_by_con_ref(tree);
	gen_getter_by_ref(tree);

	gen_getter_by_val(scope_num);
	//gen_getter_by_val(scope_lev);
};


#endif		// symbol_table_base_class_hpp
