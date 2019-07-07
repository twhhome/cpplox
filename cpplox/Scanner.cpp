#include "Scanner.h"
#include <math.h>

Scanner::Scanner(char* source)
{
	this->source = source;

	keywords.insert(std::pair<char*, TokenType>((char*)"and", AND));
	keywords.insert(std::pair<char*, TokenType>((char*)"class", CLASS));
	keywords.insert(std::pair<char*, TokenType>((char*)"else", ELSE));
	keywords.insert(std::pair<char*, TokenType>((char*)"false", FALSE));
	keywords.insert(std::pair<char*, TokenType>((char*)"for", FOR));
	keywords.insert(std::pair<char*, TokenType>((char*)"fun", FUN));
	keywords.insert(std::pair<char*, TokenType>((char*)"if", IF));
	keywords.insert(std::pair<char*, TokenType>((char*)"nil", NIL));
	keywords.insert(std::pair<char*, TokenType>((char*)"or", OR));
	keywords.insert(std::pair<char*, TokenType>((char*)"print", PRINT));
	keywords.insert(std::pair<char*, TokenType>((char*)"return", RETURN));
	keywords.insert(std::pair<char*, TokenType>((char*)"super", SUPER));
	keywords.insert(std::pair<char*, TokenType>((char*)"this", THIS));
	keywords.insert(std::pair<char*, TokenType>((char*)"true", TRUE));
	keywords.insert(std::pair<char*, TokenType>((char*)"var", VAR));
	keywords.insert(std::pair<char*, TokenType>((char*)"while", WHILE));
}

std::list<Token> Scanner::scanTokens() {
	while (!isAtEnd()) {
		start = current;
		scanToken();
	}

	tokens.push_back(Token(C_EOF, (char*)"", (char*)"", NULL, line));
	return tokens;
}

void Scanner::scanToken() {
	char c = advance();
	switch (c)
	{
	case '(': addToken(LEFT_PAREN); break;
	case ')': addToken(RIGHT_PAREN); break;
	case '{': addToken(LEFT_BRACE); break;
	case '}': addToken(RIGHT_BRACE); break;
	case ',': addToken(COMMA); break;
	case '.': addToken(DOT); break;
	case '-': addToken(MINUS); break;
	case '+': addToken(PLUS); break;
	case ';': addToken(SEMICOLON); break;
	case '*': addToken(STAR); break;
	case '!': addToken(match('=') ? BANG_EQUAL : BANG); break;
	case '=': addToken(match('=') ? EQUAL_EQUAL : EQUAL); break;
	case '<': addToken(match('=') ? LESS_EQUAL : LESS); break;
	case '>': addToken(match('=') ? GREATER_EQUAL : GREATER); break;
	case '/':
		if (match('/')) {
			while (peek() != '\n' && !isAtEnd()) {
				advance();
			}
		}
		else {
			addToken(SLASH);
		}
		break;
		
	case ' ':
	case '\r':
	case '\t':
		break;

	case '\n':
		line++;
		break;

	case '"': string(); break;

	default:
		if (isDigit(c)) {
			number();
		}
		else if (isAlpha(c)) {
			identifier();
		}
		else {
			error(line, (char*)"Unexpected character.");
		}
		break;
	}
}

void Scanner::identifier() {
	while (isAlphaNumeric(peek())) advance();

	char text[100];
	int len = 0;
	for (int i = start; i <= current; i++) {
		text[len++] = source[i];
	}
	text[len] = '\0';

	std::map<char*, TokenType>::iterator it;
	TokenType type;
	it = keywords.find(text);
	if (it != keywords.end()) {
		type = it->second;
	}
	else {
		type = IDENTIFIER;
	}
	addToken(type);
}

void Scanner::number() {
	while (isDigit(peek())) advance();

	if (peek() == '.' && isDigit(peekNext())) {
		advance();

		while (isDigit(peek())) advance();
	}

	char text[100];
	int len = 0;
	for (int i = start; i <= current; i++) {
		text[len++] = source[i];
	}
	text[len] = '\0';

	addToken(NUMBER, stringtodouble(text));
}

void Scanner::string() {
	while (peek() != '"' && !isAtEnd()) {
		if (peek() == '\n') line++;
		advance();
	}

	if (isAtEnd()) {
		error(line, (char*)"Unterminated string.");
		return;
	}

	advance();

	char text[1000];
	int len = 0;
	for (int i = start + 1; i <= current - 1; i++) {
		text[len++] = source[i];
	}
	text[len] = '\0';
	addToken(STRING, text);
}

bool Scanner::match(char expected) {
	if (isAtEnd()) return false;
	if (source[current] != expected) return false;

	current++;
	return true;
}

char Scanner::peek() {
	if (isAtEnd()) return '\0';
	return source[current];
}

char Scanner::peekNext() {
	if (current + 1 > strlen(source)) return '\0';
	return source[current + 1];
}

bool Scanner::isAlpha(char c) {
	return (c >= 'a' && c <= 'z') ||
		(c >= 'A' && c <= 'Z') ||
		c == '_';
}

bool Scanner::isAlphaNumeric(char c) {
	return isAlpha(c) || isDigit(c);
}

bool Scanner::isDigit(char c) {
	return c >= '0' && c <= '9';
}

bool Scanner::isAtEnd() {
	return current >= strlen(source);
}

char Scanner::advance() {
	current++;
	return source[current - 1];
}

void Scanner::addToken(TokenType type) {
	addToken(type, (char*)NULL);
}

void Scanner::addToken(TokenType type, char* literal_string) {
	char text[100];
	int len = 0;
	for (int i = start; i <= current; i++) {
		text[len++] = source[i];
	}
	text[len] = '\0';
	tokens.push_back(Token(type, text, literal_string, line));
}

void Scanner::addToken(TokenType type, double literal_number) {
	char text[100];
	int len = 0;
	for (int i = start; i <= current; i++) {
		text[len++] = source[i];
	}
	text[len] = '\0';
	tokens.push_back(Token(type, text, literal_number, line));
}

double stringtodouble(char* string) {
	char* dot = strchr(string, '.');
	int dot_index = strlen(string);
	if (dot != NULL) {
		dot_index = dot - string;
	}

	double num = 0;
	for (int i = 0; i < strlen(string); i++) {
		if (i < dot_index) {
			num += (string[i] - '0') * pow(10, dot_index - i - 1);
		}
		else if (i > dot_index) {
			num += (string[i] - '0') * pow(0.1, i - dot_index);
		}
	}
	return num;
}