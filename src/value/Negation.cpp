#include "value/Negation.h"


Negation::Negation(Cond *c){
	cond = c;
}


Cond *Negation::getCond(){
	return cond;
}
