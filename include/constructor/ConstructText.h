#ifndef CONSTRUCTTEXT_H
#define CONSTRUCTTEXT_H

#include <string>
#include "value/Char.h"
#include "value/String.h"


std::string constructString(String *in);

std::string constructChar(Char *in);

std::string constructText(Text *in);

#endif
