#include "value/Long.h"


Long::Long(){
	literal = false;
	value = 0;
}

Long::Long(long v){
	literal = true;
	value = v;
}

Long::Long(std::string s, mutator m) : Num("long", s, m){
	literal = false;
	value = 0;
}

Long::Long(std::string n, std::vector<Value *> p) : Num("long", n, p){
	literal = false;
	value = 0;
}


bool Long::isLiteral(){
	return literal;
}

long Long::getValue(){
	return value;
}
