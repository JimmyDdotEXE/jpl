#ifndef SHORT_H
#define SHORT_H

#include <string>
#include <vector>
#include "value/Num.h"

class Short : public Num{
public:
	Short();
	Short(short v);
	Short(std::string s, mutator m=mut_NONE);
	Short(std::string n, std::vector<Value *> p);

	bool isLiteral();
	short getValue();

private:
	bool literal;
	short value;

};
#endif
