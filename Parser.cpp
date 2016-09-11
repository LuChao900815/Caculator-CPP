#include "Parser.h"
#include "Scanner.h"
#include "Node.h"
#include "STORAGE.h"
#include <cassert>
#include <iostream>
#include "Exception.h"
#include <cstring>
#include "DebugNew.h"


Parser::~Parser(void)
{
	//delete tree_;
}

double Parser::Calculate() const
{
	assert(tree_.get() != NULL);
	return tree_->Calc();
}

STATUS Parser::Parse() 
{
	tree_ = Expr();
	if(!scanner_.IsDone())
	{
		return STATUS_ERROR;
	}
	return status_;
}

std::auto_ptr<Node> Parser::Expr()
{
	std::auto_ptr<Node> node = Term();
	EToken token = scanner_.Token();
	/*if(token == TOKEN_PLUS)
	{
		scanner_.Accept();
		Node* right = Expr();
		node = new AddNode(node,right);
	}
	else if(token == TOKEN_MINUS)
	{
		scanner_.Accept();
		Node* right = Expr();
		node = new SubNode(node,right);
	}*/
	if(token == TOKEN_PLUS || token == TOKEN_MINUS)
	{
		std::auto_ptr<MultipleNode> mNode = std::auto_ptr<MultipleNode>(new SumNode(node));
		do
		{
			scanner_.Accept();
			std::auto_ptr<Node> nNode = Term();
			mNode->AppendChild(nNode,token == TOKEN_PLUS);
			token = scanner_.Token();
		}while(token == TOKEN_PLUS || token == TOKEN_MINUS);
		node = std::auto_ptr<Node>(mNode);
	}
	else if(token == TOKEN_ASSIGN)
	{
		//Expr := Term = Expr
		scanner_.Accept();
		std::auto_ptr<Node> nodeRight = Expr();
		if(node->IsLValue())
		{
			node = std::auto_ptr<Node>(new AssignNode(node,nodeRight));
		}
		else
		{
			status_ = STATUS_ERROR;
			//todo throw exception
			//std::cout << "this is not allowed to assign to non left-handle value." << std::endl;
			//
			throw SyntaxError("this is not allowed to assign to non left-handle value.");
		}
	}
	return node;
}

std::auto_ptr<Node> Parser::Term()
{
	std::auto_ptr<Node> node = Factor();
	EToken token = scanner_.Token();
	/*if(token == TOKEN_MULTIPLY)
	{
		scanner_.Accept();
		Node* right = Term();
		node = new MultiplyNode(node,right);
	}
	else if(token == TOKEN_DIVIDE)
	{
		scanner_.Accept();
		Node* right = Term();
		node = new DivideNode(node,right);
	}*/
	
	if(token == TOKEN_MULTIPLY || token == TOKEN_DIVIDE)
	{
		std::auto_ptr<MultipleNode> mNode(new ProductNode(node));
		do
		{
			scanner_.Accept();
			std::auto_ptr<Node> nNode = Factor();
			mNode->AppendChild(nNode,token == TOKEN_MULTIPLY);
			token = scanner_.Token();
		}while(token == TOKEN_MULTIPLY || token == TOKEN_DIVIDE);
		node = mNode;
	}
	return node;
}

std::auto_ptr<Node> Parser::Factor()
{
	EToken token = scanner_.Token();
	std::auto_ptr<Node> node;

	if(token == TOKEN_NUMBER)
	{
		scanner_.Accept();
		node = std::auto_ptr<Node>(new NumberNode(scanner_.Number()));
		return node;
	}
	else if(token == TOKEN_LPARENTHESIS)
	{
		scanner_.Accept(); //accept '('
		node = Expr();
		if(scanner_.Token() == TOKEN_RPARENTHESIS)
		{
			scanner_.Accept();
		}
		else
		{
			status_ = STATUS_ERROR;
			//Todo: throw exception
			//std::cout << " not a invalid expression : miss ) " << std::endl;
			throw SyntaxError(" not a invalid expression : miss ) ");
			//node = 0;
		}
	}
	else if(token == TOKEN_IDENTIFIER)
	{
		scanner_.Accept();
		std::string symbol = scanner_.GetSymbol();
		unsigned int id = calc_.FindSymbol(symbol);

		if(scanner_.Token() == TOKEN_LPARENTHESIS)
		{
			scanner_.Accept();
			node = Expr();
			if(scanner_.Token() == TOKEN_RPARENTHESIS)
			{
				scanner_.Accept();
				if(id != (unsigned int) -1 && calc_.IsFunction(id))
				{
					node = std::auto_ptr<Node>(new FunctionNode(node,calc_.GetFun(id)));
				}
				else
				{
					//std::cout << symbol <<  " is not a function!!!" << std::endl;
					//status_ = STATUS_ERROR;
					char buf[256] = {0};
					sprintf(buf,"Unknown function \"%s\".",symbol.c_str());
					throw Exception(buf);
				}
			}
			else
			{
				//std::cout << "in function call missing ) " << std::endl;
				//status_ = STATUS_ERROR;
				throw Exception("in function call missing )");
			}
		}
		else
		{
			if(id == (unsigned int) -1)
			{
				id = calc_.AddSymbol(symbol);
			}

			node = std::auto_ptr<Node>(new VariableNode(id,calc_.GetStorage()));
		}

		
	}
	else if(token == TOKEN_MINUS)
	{
		scanner_.Accept();
		node = std::auto_ptr<Node>(new UMinusNode(Factor()));
	}
	else
	{
		status_ = STATUS_ERROR;
		throw Exception("not valid expression!");
	}
	return node;
}