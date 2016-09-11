#pragma once
#ifndef _FUNCTIONTABLE_H_
#define _FUNCTIONTABLE_H_

typedef double (*PtrFun)(double);

class SymbolTable;

class FunctionTable
{
public:
	FunctionTable(SymbolTable& tbl);
	~FunctionTable(void);

	void Init(SymbolTable& tbl);

	PtrFun GetFun(unsigned int id)
	{
		return pFuns_[id];
	}

	unsigned int Size() const
	{
		return size_;
	}
private:
	PtrFun* pFuns_;
	unsigned int size_;
};

#endif//_FUNCTIONTABLE_H_

