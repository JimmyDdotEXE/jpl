#include "value/Group.h"


Group::Group(Num *n){
	num = n;
}

Group::Group(Cond *c){
	cond = c;
}


Num *Group::getNum(){
	return num;
}

Cond *Group::getCond(){
	return cond;
}
