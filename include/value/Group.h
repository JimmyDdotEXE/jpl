#ifndef GROUP_H
#define GROUP_H

#include "value/Num.h"
#include "value/Cond.h"


class Group : public Num, public Cond{
public:
	Group(Num *n);
	Group(Cond *c);

	Num *getNum();
	Cond *getCond();

private:
	Num *num;
	Cond *cond;

};
#endif
