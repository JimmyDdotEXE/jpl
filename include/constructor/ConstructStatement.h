#ifndef CONSTRUCTSTATEMENT_H
#define CONSTRUCTSTATEMENT_H

#include <string>
#include "statement/Statement.h"


std::string constructStatement(Statement *in);


std::vector<std::string> constructGlobalDeclarations(std::vector<global_t> g);
std::vector<std::string> constructGlobalDefinitions(std::vector<global_t> g);

#endif
