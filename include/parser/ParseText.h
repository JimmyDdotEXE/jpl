#ifndef PARSETEXT_H
#define PARSETEXT_H

#include <string>
#include <vector>
#include "value/Char.h"
#include "value/String.h"


Text *parseTextDeclaration(std::vector<std::string> in);

String *parseString(std::vector<std::string> in, bool guaranteedText=true, bool tryVar=true);

Char *parseChar(std::vector<std::string> in, bool guaranteedText=true, bool tryVar=true);

Text *parseText(std::vector<std::string> in, bool guaranteedText=true, bool tryVar=true);

#endif
