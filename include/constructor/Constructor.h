#ifndef CONSTRUCTOR_H
#define CONSTRUCTOR_H

#include "File.h"
#include "value/Value.h"


bool clearConstructorScope();

bool addToScope(Value *var);

bool checkScope(Value *var);

std::vector<std::string> constructor(std::vector<line_t> lines, bool needMain=false);
std::vector<File *> constructor(std::vector<File *> files);

#endif
