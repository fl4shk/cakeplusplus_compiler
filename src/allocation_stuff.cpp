#include "allocation_stuff.hpp"

//std::set<std::string> pool_for_cstm_strdup;
std::vector<std::unique_ptr<std::string>> pool_for_cstm_strdup;

//std::map<int, size_t> indices_for_cstm_intdup;
std::vector<std::unique_ptr<int>> pool_for_cstm_intdup;


extern "C"
{
const char* __cstm_strdup_innards(char* some_c_str)
{
	//pool_for_cstm_strdup.push_back(std::string(some_c_str));
	pool_for_cstm_strdup.push_back(std::unique_ptr<std::string>());
	pool_for_cstm_strdup.back().reset(new std::string(some_c_str));
	return pool_for_cstm_strdup.back()->c_str();
}
const char* cstm_strdup(char* some_c_str)
{
	////pool_for_cstm_strdup.push_back(std::string(some_c_str));

	////printout("aaaa\n");
	//pool_for_cstm_strdup.insert(std::string(some_c_str));
	////printout("bbbb\n");

	////return pool_for_cstm_strdup.back().c_str();
	//return pool_for_cstm_strdup.find(std::string(some_c_str))->c_str();

	printout("cstm_strdup():  ", some_c_str, "\n");

	////pool_for_cstm_strdup.push_back(std::string(some_c_str));
	//pool_for_cstm_strdup.push_back(std::unique_ptr<std::string>());
	//pool_for_cstm_strdup.back().reset(new std::string(some_c_str));
	//return pool_for_cstm_strdup.back()->c_str();

	const char* temp = __cstm_strdup_innards(some_c_str);
	printout("cstm_strdup():  ", temp, "\n");
	return temp;

}

const int* cstm_intdup(int num)
{
	//printout("cstm_intdup():  Searching for ", num, "!\n");
	//auto search = indices_for_cstm_intdup.find(num);

	//if (search != indices_for_cstm_intdup.end())
	//{
	//	return (pool_for_cstm_intdup.at(search->second)).get();
	//}

	//const size_t some_size = pool_for_cstm_intdup.size();
	//indices_for_cstm_intdup[num] = some_size;

	//printout("cstm_intdup():  Creating new integer:  ", 
	//	strappcom2(num, some_size), "!\n");
	//std::unique_ptr<int> to_push;
	//to_push.reset(new int());
	//*to_push = num;
	//pool_for_cstm_intdup.push_back(std::move(to_push));

	//return pool_for_cstm_intdup.back().get();

	//std::unique_ptr<int> to_push;
	//to_push.reset(new int());
	//*to_push = num;


	//int* ret = to_push.get();

	printout("cstm_intdup():  ", num, "\n");
	//pool_for_cstm_intdup.push_back(std::move(to_push));
	pool_for_cstm_intdup.push_back(std::unique_ptr<int>());
	pool_for_cstm_intdup.back().reset(new int());
	*pool_for_cstm_intdup.back() = num;

	return pool_for_cstm_intdup.back().get();

}
}
