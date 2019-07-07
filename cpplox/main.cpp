#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string>

//#include "error.h"
#include "Scanner.h"
/*
void error(int line, char* message);
void error(Token token, char* message);
void report(int line, char* where, char* message);
*/
void runFile(char* path);
void runPrompt();
void run(char* source);

int main(int argc, char **argv) {
	if (argc > 2) {
		std::cout << "Usage: cpplox [srcipt]\n";
		return 0;
	}
	else if (argc == 2) {
		runFile(argv[1]);
	}
	else {
		runPrompt();
	}

	system("pause");
	return 0;
}

void runFile(char* path) {
	FILE *fp;
	fopen_s(&fp, path, "r");
	getc(fp);
	if (feof(fp)) {
		std::cout << "The file is empty.\n";
		return;
	}
	else {
		rewind(fp);

		char *source = new char[1000];
		int index = 0;
		
		while (1) {
			char c = fgetc(fp);
			if (feof(fp))
				break;
			source[index++] = c;
		}
		source[index++] = '\0';

		run(source);

		free(source);

		if (hadError) exit(-1);
		if (hadRuntimeError) exit(-2);
	}
	fclose(fp);
}

void runPrompt() {
	while (1) {
		std::cout << "> ";
		char str[100];
		gets_s(str);
		run(str);
		hadError = false;
	}
}

void run(char* source) {

}