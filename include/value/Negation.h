#ifndef NEGATION_H
#define NEGATION_H

#include "value/Cond.h"


class Negation: public Cond{
public:
	Negation(Cond *c);

	Cond *getCond();

private:
	Cond *cond;

};
#endif
