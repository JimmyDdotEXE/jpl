#include "value/Byte.h"


Byte::Byte(){
	literal = false;
	value = 0;
}

Byte::Byte(char v){
	literal = true;
	value = v;
}

Byte::Byte(std::string s, mutator m) : Num("signed char", s, m){
	literal = false;
	value = 0;
}

Byte::Byte(std::string n, std::vector<Value *> p) : Num("signed char", n, p){
	literal = false;
	value = 0;
}


bool Byte::isLiteral(){
	return literal;
}

char Byte::getValue(){
	return value;
}
