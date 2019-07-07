#pragma once

#include <iostream>
#include <string.h>
#include "Token.h"

static bool hadError = false;
static bool hadRuntimeError = false;

void error(int line, char* message);
void error(Token token, char* message);
void report(int line, char* where, char* message);