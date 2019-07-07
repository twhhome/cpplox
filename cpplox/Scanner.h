#pragma once

#include <list>
#include <map>
#include <string>
#include "Token.h"
#include "error.h"

class Scanner
{
public:
	Scanner(char* source);
	std::list<Token> scanTokens();

private:
	char* source;
	std::list<Token> tokens;
	int start = 0;
	int current = 0;
	int line = 1;
	std::map<char*, TokenType> keywords;

	void scanToken();
	void identifier();
	void number();
	void string();

	bool match(char expected);
	char peek();
	char peekNext();
	bool isAlpha(char c);
	bool isAlphaNumeric(char c);
	bool isDigit(char c);
	bool isAtEnd();
	char advance();
	void addToken(TokenType type);
	void addToken(TokenType type, char* literal_string);
	void addToken(TokenType type, double literal_number);
};

double stringtodouble(char* string);