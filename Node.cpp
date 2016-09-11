#include "Node.h"
#include <cmath>
#include <iostream>
#include "STORAGE.h"
#include "Exception.h"
#include "DebugNew.h"

Node::~Node(void)
{
}

BinaryNode::~BinaryNode()
{
	//delete left_;
	//delete right_;
}

MultipleNode::~MultipleNode()
{
	for(std::vector<Node*>::const_iterator it = childs_.begin(); it != childs_.end() ;++it)
	{
		delete (*it);
	}
}

UnaryNode::~UnaryNode()
{
	//delete child_;
}

double NumberNode::Calc() const
{
	return number_;
}

//double AddNode::Calc() const
//{
//	return left_->Calc() + right_->Calc();
//}
//
//double SubNode::Calc() const
//{
//	return left_->Calc() - right_->Calc();
//}
//
//double MultiplyNode::Calc() const
//{
//	return left_->Calc() * right_->Calc();
//}
//
//double DivideNode::Calc() const
//{
//	double divisor = right_->Calc();
//	if(divisor != 0.0)
//	{
//		return left_->Calc() / divisor;
//	}
//	else
//	{
//		std::cout << "Error: Divisor is 0" << std::endl;
//		return HUGE_VAL;
//	}
//}

double UMinusNode::Calc() const
{
	return -child_->Calc();
}

double SumNode::Calc() const
{
	double sum = 0.0;
	//assert()
	for(unsigned int i = 0; i < childs_.size(); ++i)
	{
		if(positives_[i])
		{
			sum += childs_[i]->Calc();
		}
		else
		{
			sum += -(childs_[i]->Calc());
		}
	}
	return sum;
}

double  ProductNode::Calc() const
{
	double val = 1.0;
	for(unsigned int i = 0; i < childs_.size(); ++i)
	{
		if(positives_[i])
		{
			val *= childs_[i]->Calc();
		}
		else if(childs_[i]->Calc() != 0.0)
		{
			val /= (childs_[i]->Calc());
		}
		else
		{
			//std::cout << "diving by zero" << std::endl;
			//return HUGE_VAL;
			throw Exception("diving by zero");
		}
	}
	return val;
}

double VariableNode::Calc() const
{
	double x = 0.0;
	if(storage_.IsInit(id_))
	{
		return x = storage_.GetValue(id_);
	}
	else
	{
		//std::cout << "unintialized variable." << std::endl;
		throw Exception("unintialized variable.");
	}
}

bool VariableNode::IsLValue() const
{
	return  true;
}

void VariableNode::Assign(double val) 
{
	storage_.SetValue(id_,val);
}

double  AssignNode::Calc() const
{
	double val = right_->Calc();
	left_->Assign(val);
	return val;
}

double FunctionNode::Calc() const
{
	return  (*pFun_)(child_->Calc());
}