#pragma once
#ifndef _SYMBOLTABLE_H_
#define _SYMBOLTABLE_H_
#include <string>
#include <map>


class SymbolTable
{
public:
	SymbolTable(void) : curId_(0){}
	~SymbolTable(void);
public:
	unsigned int Add(const std::string& str);
	unsigned int Find(const std::string& str);
	void Clear();
	std::string GetSymbolTable(unsigned int id) const;
private:
	std::map< const std::string,unsigned int> dictionary_;
	unsigned int curId_;
};

#endif //_SYMBOLTABLE_H_
