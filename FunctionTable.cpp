#include "FunctionTable.h"
#include <cmath>
#include "SymbolTable.h"
#include <iostream>
#include "DebugNew.h"
#define func(A) {A,#A}

struct FunctionEntry
{
	PtrFun pFun_;
	char* funcName_;
};

FunctionEntry Entrys[] = 
{
	func(log),
	func(log10),
	func(exp),
	func(sqrt),
	func(sin),
	func(cos),
	func(tan),
	func(sinh),
	func(cosh),
	func(tanh),
	func(asin),
	func(acos),
	func(atan)
};

FunctionTable::FunctionTable(SymbolTable& tbl) : size_(sizeof(Entrys) / sizeof(Entrys[0]))
{
	Init(tbl);
}

void FunctionTable::Init(SymbolTable& tbl)
{
	std::cout << "function list: " << std::endl;
	pFuns_ = new PtrFun[size_];
	for(unsigned int i = 0; i < size_; ++i)
	{
		pFuns_[i] = Entrys[i].pFun_;
		tbl.Add(Entrys[i].funcName_); 
		std::cout << Entrys[i].funcName_ << std::endl;
	}	
}


FunctionTable::~FunctionTable(void)
{
	delete[] pFuns_;
}
