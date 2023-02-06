#ifndef PARSENUM_H
#define PARSENUM_H

#include <string>
#include <vector>
#include "value/Num.h"


Num *parseNumDeclaration(std::vector<std::string> in);

Num *parseNum(std::vector<std::string> in, bool guaranteedNum=true, bool tryVar=true);

#endif
