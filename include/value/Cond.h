#ifndef COND_H
#define COND_H

#include <string>
#include <vector>
#include "value/Value.h"

class Cond : public Value{
public:
	virtual ~Cond();
	Cond();
	Cond(std::string t, std::string n, mutator m=mut_NONE);
	Cond(std::string t, std::string n, std::vector<Value *> p);

};
#endif
