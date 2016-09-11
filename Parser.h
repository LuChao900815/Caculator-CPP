#pragma once
#ifndef _PARSER_H_
#define _PARSER_H_
#include "Calc.h"

class Scanner;
class Node;
//class Calc;

enum STATUS
{
	STATUS_OK,
	STATUS_ERROR,
	STATUS_QUIT
};

class Parser
{
public:
	Parser(Scanner& scanner,Calc& calc) : scanner_(scanner)
							   ,tree_(0),calc_(calc),status_(STATUS_OK){}
	~Parser(void);
public:
	STATUS Parse();
	double Calculate() const;
	std::auto_ptr<Node> Expr();
	std::auto_ptr<Node> Term();
	std::auto_ptr<Node> Factor();
private:
	Scanner&        scanner_;
	Calc&			calc_;
	std::auto_ptr<Node>			tree_;
	STATUS			status_;
};
#endif //_PARSER_H_
