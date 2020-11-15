#include "value/Concatenation.h"


Concatenation::Concatenation(Text *l, Text *r){
	lhs = l;
	rhs = r;
}


Text *Concatenation::getLeft(){
	return lhs;
}

Text *Concatenation::getRight(){
	return rhs;
}
