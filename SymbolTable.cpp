#include "SymbolTable.h"
#include <algorithm>
#include "Exception.h"

SymbolTable::~SymbolTable(void)
{
}

//将符号添加到符号表中，并分配id
unsigned int SymbolTable::Add(const std::string& str)
{
	dictionary_[str] = curId_;
	return curId_++;
}
//寻找str所对应的id
unsigned int SymbolTable::Find(const std::string& str)
{
	std::map<const std::string,unsigned int>::const_iterator 
		it = dictionary_.find(str);
	if(it != dictionary_.end())
	{
		return it->second;
	}
	return -1;
}
// 清除符号表
void SymbolTable::Clear()
{
	dictionary_.clear();
	curId_ = 0;
}

/**
*/
class IsEqualId
{
public:
	IsEqualId(unsigned int id) : id_(id){}
	bool operator()(const std::pair<const std::string,unsigned int>& it)
	{
		return it.second == id_;
	}
private:
	unsigned int id_;
};

//获取id所对应的符号名
std::string SymbolTable::GetSymbolTable(unsigned int id) const
{
	std::map<const std::string,unsigned int>::const_iterator 
		it = dictionary_.begin();
	it = std::find_if(dictionary_.begin(),dictionary_.end(),IsEqualId(id));
	if(it != dictionary_.end())
	{
		return it->first;
	}else{
		throw Exception("Internal error: missing entry in symbol table");
	}
}
