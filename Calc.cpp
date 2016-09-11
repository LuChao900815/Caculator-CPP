#include "Calc.h"


Calc::Calc(void) : funTbl_(symTbl_),storage_(symTbl_)
{
}


Calc::~Calc(void)
{
}


unsigned int Calc::FindSymbol(const std::string& sym)
{
	return symTbl_.Find(sym);
}

unsigned int Calc::AddSymbol(const std::string& sym)
{
	return symTbl_.Add(sym);
}