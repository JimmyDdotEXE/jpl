#ifndef BOOL_H
#define BOOL_H

#include <string>
#include <vector>
#include "value/Cond.h"

class Bool : public Cond{
public:
	Bool();
	Bool(bool v);
	Bool(std::string s, mutator m=mut_NONE);
	Bool(std::string n, std::vector<Value *> p);

	bool isLiteral();
	bool getValue();

private:
	bool literal;
	bool value;

};
#endif
