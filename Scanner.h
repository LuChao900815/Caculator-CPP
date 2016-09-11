#pragma once
#ifndef _SCANNER_H_
#define _SCANNER_H_
#include <string>

enum EToken
{
	TOKEN_BEGIN,
	TOKEN_END,
	TOKEN_ERROR,
	TOKEN_NUMBER,
	TOKEN_PLUS,
	TOKEN_MINUS,
	TOKEN_MULTIPLY,
	TOKEN_DIVIDE,
	TOKEN_LPARENTHESIS,
	TOKEN_RPARENTHESIS,
	TOKEN_IDENTIFIER,
	TOKEN_ASSIGN,
	//TOKEN_END
};

class Scanner
{
public:
	Scanner(const std::string& buf) : buf_(buf)
		,curPos_(0),token_(TOKEN_BEGIN),number_(0)
	{
		Accept();
		isEmpty = (token_ == TOKEN_END);
	}
	virtual ~Scanner(void);

public:
	void Accept();
	double Number() const;
	EToken Token() const;
	void SkipWhite();
	std::string getTokenString() const; 
	std::string GetSymbol() const;
	bool IsEmpty() const;
	bool IsDone() const;
private:
	const std::string& buf_;
	unsigned int curPos_;
	EToken token_;
	double number_;
	std::string symbol_;
	bool isEmpty;
};
#endif//_SCANNER_H_
