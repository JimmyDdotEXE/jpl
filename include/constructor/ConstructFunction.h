#ifndef CONSTRUCTFUNCTION_H
#define CONSTRUCTFUNCTION_H

#include <string>
#include <vector>
#include "value/Value.h"
#include "statement/Function.h"

std::string constructFunctionCall(Value *in);

std::string constructFunctionHeader(Function *in);
std::vector<std::string> constructFunctionHeaders(std::vector<Function *> in);

std::vector<std::string> constructFunction(Function *in);
std::vector<std::string> constructFunctions(std::vector<Function *> in);

#endif
