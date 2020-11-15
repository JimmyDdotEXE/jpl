#include "value/Long.h"


Long::Long(){
	literal = false;
	value = 0;
}

Long::Long(long v){
	literal = true;
	value = v;
}

Long::Long(std::string s) : Num("long", s){
	literal = false;
	value = 0;
}


bool Long::isLiteral(){
	return literal;
}

long Long::getValue(){
	return value;
}
