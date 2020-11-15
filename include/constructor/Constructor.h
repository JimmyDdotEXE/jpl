#ifndef CONSTRUCTOR_H
#define CONSTRUCTOR_H

#include "parser/Parser.h"
#include "value/Value.h"


bool addToScope(Value *var);

bool checkScope(Value *var);

std::vector<std::string> constructor(std::vector<line_t> input);

#endif
