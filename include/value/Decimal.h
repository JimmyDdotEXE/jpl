#ifndef DECIMAL_H
#define DECIMAL_H

#include <string>
#include <vector>
#include "value/Num.h"

class Decimal : public Num{
public:
	Decimal();
	Decimal(double v);
	Decimal(std::string s, mutator m=mut_NONE);
	Decimal(std::string n, std::vector<Value *> p);

	bool isLiteral();
	double getValue();

private:
	bool literal;
	double value;

};
#endif
