#ifndef PARSECOND_H
#define PARSECOND_H

#include <string>
#include <vector>
#include "value/Cond.h"


Cond *parseCondDeclaration(std::vector<std::string> in);

Cond *parseCond(std::vector<std::string> in, bool guaranteedCond=true, bool tryVar=true);

#endif
