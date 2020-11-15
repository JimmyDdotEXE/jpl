#ifndef CONATENATION_H
#define CONATENATION_H

#include "value/String.h"


class Concatenation: public String{
public:
	Concatenation(Text *l, Text *r);

	Text *getLeft();
	Text *getRight();

private:
	Text *lhs;
	Text *rhs;

};
#endif
