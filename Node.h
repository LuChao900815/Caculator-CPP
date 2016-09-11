#pragma once
#ifndef _NODE_H_
#define _NODE_H_
#include <vector>
#include <cassert>
#include "FunctionTable.h"

class Storage;

class Noncopyable
{
protected:
	Noncopyable() {}
	virtual ~Noncopyable(){}
private:
	Noncopyable(const Noncopyable&);
	const Noncopyable& operator=(const Noncopyable&);
};

class Node : private Noncopyable
{
public:
	virtual double Calc()  const = 0;
	virtual bool IsLValue() const
	{
		return false;
	}
	virtual void Assign(double val) 
	{
		assert(!"Assign called incorrectly.");
	}
	virtual ~Node(void);
};


class NumberNode : public Node
{
public:
	NumberNode(double number) : number_(number){}
	double Calc() const;
private:
	 const double number_;
};

class UnaryNode : public Node
{
public:
	UnaryNode(std::auto_ptr<Node>& child) 
		: child_(child){}
	~UnaryNode();
protected:
//	Node* child_;
	std::auto_ptr<Node> child_;
};

class BinaryNode : public Node
{
public:
	BinaryNode(std::auto_ptr<Node>& left,std::auto_ptr<Node>& right)
		: left_(left),right_(right){} 
	~BinaryNode();
protected:
	 //Node* const left_;
	 //Node* const right_;
	std::auto_ptr<Node> left_;
	std::auto_ptr<Node> right_;
};

class MultipleNode : public Node
{
public:
	MultipleNode(std::auto_ptr<Node>& node)
	{
		AppendChild(node,true);
	}
	~MultipleNode();
public:
	void AppendChild(std::auto_ptr<Node>& node,bool positive)
	{
		childs_.push_back(node.release());
		positives_.push_back(positive);
	}
protected:
	std::vector<Node*> childs_;
	std::vector<bool>  positives_;
};

//class AddNode : public BinaryNode
//{
//public:
//	AddNode(Node* left,Node* right) 
//		: BinaryNode(left,right){}
//	double Calc() const;
//};
//
//class SubNode : public BinaryNode
//{
//public:
//	SubNode(Node* left,Node* right) 
//		: BinaryNode(left,right){}
//	double Calc() const;
//};
//
//class MultiplyNode : public BinaryNode
//{
//public:
//	MultiplyNode(Node* left,Node* right) 
//		: BinaryNode(left,right){}
//	double Calc() const;
//};
//
//class DivideNode : public BinaryNode
//{
//public:
//	DivideNode(Node* left,Node* right) 
//		: BinaryNode(left,right){}
//	double Calc() const;
//};

class UMinusNode : public UnaryNode
{
public:
	UMinusNode(std::auto_ptr<Node>& child)
		:UnaryNode(child){}
	double Calc() const;
};


class SumNode : public MultipleNode
{
public:
	SumNode(std::auto_ptr<Node>& node) 
		: MultipleNode(node){}
	double Calc() const;
};

class ProductNode : public MultipleNode
{
public:
	ProductNode(std::auto_ptr<Node>& node) 
		: MultipleNode(node){}
	double Calc() const;
};

class VariableNode : public Node
{
public:
	VariableNode(unsigned int id, Storage& storage)
		: id_(id),storage_(storage){}
	double  Calc() const;
	bool IsLValue() const;
	void Assign(double);
private:
	Storage& storage_;
	unsigned int id_;

};

class AssignNode : public BinaryNode
{
public:
	AssignNode(std::auto_ptr<Node>& left,std::auto_ptr<Node>& right) 
		: BinaryNode(left,right)
	{
		assert(left->IsLValue());
	}
	double Calc() const;
};

class FunctionNode : public UnaryNode
{
public:
	FunctionNode(std::auto_ptr<Node>& child,PtrFun pFun)
		:UnaryNode(child),pFun_(pFun){}
	double Calc() const;
private:
	PtrFun pFun_;
};

#endif //_NODE_H_
