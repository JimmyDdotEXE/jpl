#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <vector>
#include "Util.h"
#include "statement/Function.h"
#include "value/Value.h"
#include "File.h"


typedef struct{
	Function *func;
	std::string file;
} func_t;


bool nameCheck(std::string s);

bool typeCheck(Value *v1, Value *v2);

bool lookupType(std::string type);

bool setScope(std::vector<Value *> in);
bool clearScope();

bool addVar(Value *var);
Value *lookupVar(std::string var);

Function *lookupFunction(std::string n);

int countExtraLines(std::vector<line_t> lines);

std::vector<line_t> parseLines(std::vector<std::string> input, int depth=0);

bool parser(std::vector<File *> files);

#endif
