#include <iostream>
#include <cstring>
#include <cctype>
#include "Scanner.h"

#define toString(A) #A

Scanner::~Scanner(void)
{
}

double Scanner::Number() const
{
	return number_;
}

EToken Scanner::Token() const
{
	return token_;
}

void Scanner::SkipWhite()
{
	while(isspace(buf_[curPos_]))
	{
		++curPos_;
	}
}

void Scanner::Accept()
{
	SkipWhite();
	char* p = 0;
	char c = buf_[curPos_];
	//std::cout << c << std::endl;
	switch(c)
	{
	case '+':
		token_ = TOKEN_PLUS;
		++curPos_;
		break;
	case '-':
		token_ = TOKEN_MINUS;
		++curPos_;
		break;
	case '*':
		token_ = TOKEN_MULTIPLY;
		++curPos_;
		break;
	case '/':
		token_ = TOKEN_DIVIDE;
		++curPos_;
		break;
	case '(':
		token_ = TOKEN_LPARENTHESIS;
		++curPos_;
		break;
	case ')':
		token_ = TOKEN_RPARENTHESIS;
		++curPos_;
		break;
	case '=':
		token_ = TOKEN_ASSIGN;
		++curPos_;
		break;
	case '0': case '1': case '2':case '3': case '4': case '5':
	case '6': case '7': case '8':case '9': case '.': 
		number_ = strtod(&buf_[curPos_],&p);
		curPos_ += (p - &buf_[curPos_]);
		token_ = TOKEN_NUMBER;
		break;
	case '\0':case '\n':case '\r':case EOF:
		token_ = TOKEN_END;
		break;

	default:

		if(isalpha(c) || c == '_')
		{
			token_ = TOKEN_IDENTIFIER;
			symbol_.erase();
			do
			{
				symbol_ += c;
				++curPos_;
				c = buf_[curPos_];
			}while(isalnum(c) || c == '_');
		}
		else
		{
			token_ = TOKEN_ERROR;
		}
		break;
	}
}

std::string Scanner::getTokenString() const
{
	switch(token_)
	{
	case TOKEN_BEGIN:
		return toString(TOKEN_BEGIN);
	case TOKEN_END:
		return toString(TOKEN_END);
	case TOKEN_ERROR:
		return toString(TOKEN_ERROR);
	case TOKEN_NUMBER:
		return toString(TOKEN_NUMBER);
	case TOKEN_PLUS:
		return toString(TOKEN_PLUS);
	case TOKEN_MINUS:
		return toString(TOKEN_MINUS);
	case TOKEN_MULTIPLY:
		return toString(TOKEN_MULTIPLY);
	case TOKEN_DIVIDE:
		return toString(TOKEN_DIVIDE);
	case TOKEN_LPARENTHESIS:
		return toString(TOKEN_LPARENTHESIS);
	case TOKEN_RPARENTHESIS:
		return toString(TOKEN_RPARENTHESIS);
	case TOKEN_IDENTIFIER:
		return toString(TOKEN_IDENTIFIER);
	case TOKEN_ASSIGN:
		return toString(TOKEN_ASSIGN);
	}
}

std::string Scanner::GetSymbol() const
{
	return symbol_;
}

bool Scanner::IsEmpty() const
{
	return isEmpty;
}

bool Scanner::IsDone() const
{
	return token_ == TOKEN_END;
}