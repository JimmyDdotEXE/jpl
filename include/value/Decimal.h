#ifndef DECIMAL_H
#define DECIMAL_H

#include <string>
#include "value/Num.h"

class Decimal : public Num{
public:
	Decimal();
	Decimal(double v);
	Decimal(std::string s);

	bool isLiteral();
	double getValue();

private:
	bool literal;
	double value;

};
#endif
