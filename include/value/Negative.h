#ifndef NEGATIVE_H
#define NEGATIVE_H

#include "value/Num.h"


class Negative: public Num{
public:
	Negative(Num *n);

	Num *getNum();

private:
	Num *num;

};
#endif
