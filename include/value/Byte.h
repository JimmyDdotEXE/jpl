#ifndef BYTE_H
#define BYTE_H

#include <string>
#include <vector>
#include "value/Num.h"

class Byte : public Num{
public:
	Byte();
	Byte(char v);
	Byte(std::string s, mutator m=mut_NONE);
	Byte(std::string n, std::vector<Value *> p);

	bool isLiteral();
	char getValue();

private:
	bool literal;
	char value;

};
#endif
