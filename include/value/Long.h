#ifndef LONG_H
#define LONG_H

#include <string>
#include <vector>
#include "value/Num.h"

class Long : public Num{
public:
	Long();
	Long(long v);
	Long(std::string s, mutator m=mut_NONE);
	Long(std::string n, std::vector<Value *> p);

	bool isLiteral();
	long getValue();

private:
	bool literal;
	long value;

};
#endif
