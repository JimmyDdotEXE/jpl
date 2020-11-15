#ifndef COND_H
#define COND_H

#include <string>
#include "value/Value.h"

class Cond : public Value{
public:
	virtual ~Cond();
	Cond();
	Cond(std::string t, std::string n);

};
#endif
