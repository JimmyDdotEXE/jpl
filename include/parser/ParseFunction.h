#ifndef PARSEFUNCTION_H
#define PARSEFUNCTION_H

#include <string>
#include <vector>
#include "value/Value.h"
#include "statement/Function.h"


std::vector<Function *> parseFunctions(std::vector<std::string> *in);

#endif
