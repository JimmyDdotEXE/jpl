#ifndef NUM_H
#define NUM_H

#include <string>
#include <vector>
#include "value/Value.h"

class Num : public Value{
public:
	virtual ~Num();
	Num();
	Num(std::string t, std::string n, mutator m=mut_NONE);
	Num(std::string t, std::string n, std::vector<Value *> p);

};
#endif
