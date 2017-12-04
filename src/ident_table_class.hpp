#ifndef ident_table_class_hpp
#define ident_table_class_hpp


#include "misc_includes.hpp"


template<typename Type>
class IdentTable
{
private:		// variables
	std::map<std::string, Type> __table;

public:		// functions
	inline IdentTable()
	{
	}

	// Type accessors
	inline Type& at(const std::string& some_name)
	{
		return __table[some_name];
	}

	inline const Type& at(const std::string& some_name) const
	{
		return __table.at(some_name);
	}

	inline bool contains(const std::string& some_name) const
	{
		return (__table.count(some_name) == 1);
	}

	inline void insert_or_assign(const Type& to_insert_or_assign)
	{
		at(to_insert_or_assign.name()) = to_insert_or_assign;
	}
	inline void insert_or_assign(Type&& to_insert_or_assign)
	{
		at(to_insert_or_assign.name()) = std::move(to_insert_or_assign);
	}

	gen_getter_by_con_ref(table);
};


#endif		// ident_table_class_hpp
