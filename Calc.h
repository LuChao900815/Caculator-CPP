#pragma once
#ifndef _CALC_H_
#define _CALC_H_
#include "SymbolTable.h"
#include "STORAGE.h"
#include "FunctionTable.h"
class Parser;

class Calc
{
	friend class Parser;
public:
	Calc(void);
	~Calc(void);
	unsigned int FindSymbol(const std::string& sym);
	unsigned int AddSymbol(const std::string& str);
	bool IsFunction(unsigned int id) const
	{
		return id < funTbl_.Size();
	}

	PtrFun GetFun(unsigned int id)
	{
		return funTbl_.GetFun(id);
	}
	Storage& GetStorage()
	{
		return storage_;
	}
private:
	SymbolTable symTbl_;
	FunctionTable funTbl_;
	Storage     storage_;
};

#endif //_CALC_H_