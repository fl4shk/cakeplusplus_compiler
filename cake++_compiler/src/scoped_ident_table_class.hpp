#ifndef scoped_ident_table_class_hpp
#define scoped_ident_table_class_hpp


#include "misc_includes.hpp"
#include "ident_table_classes.hpp"

// This is kind of like a stack
template<typename Type>
class ScopedIdentTable
{
public:		// typedefs and constants
	typedef IdentTable<Type> OneLevelTable;

	static constexpr s64 builtin_scope_level = 0;
	static constexpr s64 not_found_level = builtin_scope_level - 1;

protected:		// variables
	std::vector<OneLevelTable> __table;


	// The number of scopes that have been made - 1
	s64 __scope_num = -1;

	

public:		// functions
	inline ScopedIdentTable()
	{
		mkscope();
	}
	virtual ~ScopedIdentTable()
	{
	}

	void mkscope() __attribute__((noinline))
	{
		table().push_back(OneLevelTable());

		++__scope_num;

		if (scope_num() < 0)
		{
			printerr("ScopedIdentTable::mkscope():  ",
				"Far, FAR too many scopes!\n");
			exit(1);
		}

		//__parallel_scope_num = 0;
	}
	//void mk_parallel_scope() __attribute__((noinline))
	//{
	//	table().back
	//}

	void rmscope() __attribute__((noinline))
	{
		if (scope_lev() > builtin_scope_level)
		{
			table().pop_back();
		}
		else
		{
			printerr("ScopedIdentTable::rmscope():  Eek!\n");
			exit(1);
		}
	}

	inline auto& at(size_t table_index)
	{
		return __table.at(table_index);
	}
	inline const auto& at(size_t table_index) const
	{
		return __table.at(table_index);
	}

	inline void insert_or_assign(const Type& to_insert_or_assign)
	{
		at(scope_lev()).insert_or_assign(to_insert_or_assign);
	}
	inline void insert_or_assign(Type&& to_insert_or_assign)
	{
		at(scope_lev()).insert_or_assign(std::move(to_insert_or_assign));
	}

	inline void insert_or_assign(size_t level, 
		const Type& to_insert_or_assign)
	{
		at(level).insert_or_assign(to_insert_or_assign);
	}
	inline void insert_or_assign(size_t level, Type&& to_insert_or_assign)
	{
		at(level).insert_or_assign(std::move(to_insert_or_assign));
	}

	Type* find(Ident some_name) __attribute__((noinline))
	{
		// Check builtins first.
		if (table().at(builtin_scope_level).contains(some_name))
		{
			//return builtin_scope_level;
			return &table().at(builtin_scope_level).at(some_name);
		}

		for (s64 i=scope_lev(); i>=builtin_scope_level; --i)
		{
			if (table().at(i).contains(some_name))
			{
				return &table().at(i).at(some_name);
			}
		}

		return nullptr;
	}

	inline Type* find_in_this_level(Ident some_name)
	{
		if (table().at(scope_lev()).contains(some_name))
		{
			return &table().at(scope_lev()).at(some_name);
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

	//inline bool contains(Ident some_name) const
	//{
	//	return (find(some_name) != nullptr);
	//}

	bool name_is_builtin(Ident some_name) const
	{
		return table().at(builtin_scope_level).contains(some_name);
	}

	gen_getter_by_con_ref(table);
	gen_getter_by_ref(table);
	inline s64 scope_lev() const
	{
		return (table().size() - 1);
	}

	gen_getter_by_val(scope_num);
};


#endif		// scoped_ident_table_class_hpp
