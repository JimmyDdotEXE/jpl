#include "value/Negative.h"


Negative::Negative(Num *n){
	num = n;
}


Num *Negative::getNum(){
	return num;
}
