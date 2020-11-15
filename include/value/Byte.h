#ifndef BYTE_H
#define BYTE_H

#include <string>
#include "value/Num.h"

class Byte : public Num{
public:
	Byte();
	Byte(char v);
	Byte(std::string s);

	bool isLiteral();
	char getValue();

private:
	bool literal;
	char value;

};
#endif
