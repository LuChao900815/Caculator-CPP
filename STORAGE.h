#pragma once
#ifndef _STORAGE_H_
#define _STORAGE_H_
#include <vector>

class SymbolTable;

class Storage
{
public:
	Storage(SymbolTable& tbl);
	~Storage(void);
public:
	void Clear();
	bool IsInit(unsigned int id) const;
	void AddConstants(SymbolTable& tbl);
	double GetValue(unsigned int id) const;
	void SetValue(unsigned int id,double value);
	void AddValue(unsigned int id,double value);
private:
	std::vector<double> cells_;
	std::vector<bool> inits_;
};

#endif//_STORAGE_H_