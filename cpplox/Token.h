#pragma once

#include "TokenType.h"

class Token {
public:
	TokenType type;
	char* lexeme;
	char* literal_string;
	double literal_number;
	int line;

	Token(TokenType type, char* lexeme, char* literal_string, int line) {
		this->type = type;
		this->lexeme = lexeme;
		this->literal_string = literal_string;
		this->line = line;
	}

	Token(TokenType type, char* lexeme, double literal_number, int line) {
		this->type = type;
		this->lexeme = lexeme;
		this->literal_number = literal_number;
		this->line = line;
	}

	Token(TokenType type, char* lexeme, char* literal_string, double literal_number, int line) {
		this->type = type;
		this->lexeme = lexeme;
		this->literal_string = literal_string;
		this->literal_number = literal_number;
		this->line = line;
	}
};