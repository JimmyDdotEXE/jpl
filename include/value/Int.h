#ifndef INT_H
#define INT_H

#include <string>
#include "value/Num.h"

class Int : public Num{
public:
	Int();
	Int(int v);
	Int(std::string s);

	bool isLiteral();
	int getValue();

private:
	bool literal;
	int value;

};
#endif
