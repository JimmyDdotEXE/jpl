#ifndef PARSEVALUE_H
#define PARSEVALUE_H

#include <string>
#include <vector>
#include "value/Value.h"


Value *parseDeclarationVar(std::vector<std::string> in);

Value *parseVar(std::vector<std::string> in);

Value *parseValue(std::vector<std::string> in);

#endif
