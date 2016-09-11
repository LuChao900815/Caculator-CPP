#include "STORAGE.h"
#include <cmath>
#include <cassert>
#include <iostream>
#include "SymbolTable.h"

Storage::Storage(SymbolTable& tbl)
{
	AddConstants(tbl);
}


Storage::~Storage(void)
{
}

void Storage::Clear()
{
	cells_.clear();
	inits_.clear();
}

//是否初始化
bool Storage::IsInit(unsigned int id) const
{
	return id < cells_.size() ? inits_[id] : false;
}
//添加常量值
void Storage::AddConstants(SymbolTable& tbl)
{
	std::cout << "variable list: " << std::endl;
	unsigned int id = tbl.Add("e");
	AddValue(id,exp(1.0));
	std::cout << "e = " << exp(1.0) << std::endl;

	id = tbl.Add("pi");
	AddValue(id,2.0 * acos(0.0)); //acos pi = 2 * acos(0)
	std::cout << "pi = " << 2.0 * acos(0.0) << std::endl;
}
//添加常量值
void Storage::AddValue(unsigned int id,double value)
{
	cells_.resize(id+1);
	inits_.resize(id+1);
	cells_[id] = value;
	inits_[id] = true;
}
//获取id对应的常量值
double Storage::GetValue(unsigned int id) const
{
	assert(id < cells_.size());
	return  cells_[id];
}
//
void Storage::SetValue(unsigned int id,double value)
{
	assert(id <= cells_.size());
	if(id < cells_.size())
	{
		cells_[id] = value;
		inits_[id] = true;
	}
	else if(id == cells_.size())
	{
		AddValue(id,value);
	}

}

