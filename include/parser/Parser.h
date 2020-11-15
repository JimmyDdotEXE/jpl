#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <vector>
#include "statement/Statement.h"
#include "value/Value.h"


typedef struct line_t{
	Statement *stmt;
	std::string comment;
	int tabDepth;
	bool live;
} line_t;


bool lookupType(std::string type);

bool addVar(Value *var);
Value *lookupVar(std::string var);

std::vector<line_t> parser(std::vector<std::string> input, int depth=0);

#endif
