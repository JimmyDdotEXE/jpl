#include "statement/Assignment.h"


Assignment::Assignment(assign o, Value *v, Value *n){
	op = o;
	lhs = v;
	rhs = n;
}


assign Assignment::getOp(){
	return op;
}

Value *Assignment::getLeft(){
	return lhs;
}

Value *Assignment::getRight(){
	return rhs;
}
