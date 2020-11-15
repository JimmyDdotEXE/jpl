#ifndef EQUATION_H
#define EQUATION_H

#include "value/Num.h"


typedef enum{ADD, SUB, MULT, DIV, POW, REM} oper;


class Equation: public Num{
public:
	Equation(oper o, Num *l, Num *r);

	oper getOp();
	Num *getLeft();
	Num *getRight();

private:
	oper op;
	Num *lhs;
	Num *rhs;

};
#endif
