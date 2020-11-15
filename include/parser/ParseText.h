#ifndef PARSETEXT_H
#define PARSETEXT_H

#include <string>
#include <vector>
#include "value/Char.h"
#include "value/String.h"


Text *parseTextDeclaration(std::vector<std::string> in);

String *parseString(std::vector<std::string> in);

Char *parseChar(std::vector<std::string> in);

Text *parseText(std::vector<std::string> in);

#endif
