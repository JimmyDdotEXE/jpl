#ifndef LONG_H
#define LONG_H

#include <string>
#include "value/Num.h"

class Long : public Num{
public:
	Long();
	Long(long v);
	Long(std::string s);

	bool isLiteral();
	long getValue();

private:
	bool literal;
	long value;

};
#endif
