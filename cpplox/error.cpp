#include "error.h"

void report(int line, char* where, char* message) {
	std::cout << "[line " << line << "] Error" << where << ": " << message << std::endl;
	hadError = true;
}

void error(int line, char* message) {
	report(line, (char*)"", message);
}

void error(Token token, char* message) {
	if (token.type == C_EOF) {
		report(token.line, (char*)" at end", message);
	}
	else {
		char str[100];
		strcpy_s(str, " at \'");
		strcat_s(str, token.lexeme);
		strcat_s(str, "\'");
		report(token.line, str, message);
	}
}