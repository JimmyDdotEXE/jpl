#ifndef PARSEVALUE_H
#define PARSEVALUE_H

#include <string>
#include <vector>
#include "File.h"
#include "value/Value.h"


std::vector<global_t> parseGlobals(std::vector<std::string> *in);

Value *parseDeclarationVar(std::vector<std::string> in);

Value *parseVar(std::vector<std::string> in);

Value *parseValue(std::vector<std::string> in);

#endif
