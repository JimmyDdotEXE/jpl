#ifndef BOOL_H
#define BOOL_H

#include <string>
#include "value/Cond.h"

class Bool : public Cond{
public:
	Bool();
	Bool(bool v);
	Bool(std::string s);

	bool isLiteral();
	bool getValue();

private:
	bool literal;
	bool value;

};
#endif
