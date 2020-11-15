#include "value/Equation.h"


Equation::Equation(oper o, Num *l, Num *r){
	op = o;
	lhs = l;
	rhs = r;
}


oper Equation::getOp(){
	return op;
}

Num *Equation::getLeft(){
	return lhs;
}

Num *Equation::getRight(){
	return rhs;
}
