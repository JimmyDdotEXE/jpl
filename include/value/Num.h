#ifndef NUM_H
#define NUM_H

#include <string>
#include "value/Value.h"

class Num : public Value{
public:
	virtual ~Num();
	Num();
	Num(std::string t, std::string n);

};
#endif
