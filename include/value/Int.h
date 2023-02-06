#ifndef INT_H
#define INT_H

#include <string>
#include <vector>
#include "value/Num.h"

class Int : public Num{
public:
	Int();
	Int(int v);
	Int(std::string s, mutator m=mut_NONE);
	Int(std::string n, std::vector<Value *> p);

	bool isLiteral();
	int getValue();

private:
	bool literal;
	int value;

};
#endif
