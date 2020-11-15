#include "value/Byte.h"


Byte::Byte(){
	literal = false;
	value = 0;
}

Byte::Byte(char v){
	literal = true;
	value = v;
}

Byte::Byte(std::string s) : Num("char", s){
	literal = false;
	value = 0;
}


bool Byte::isLiteral(){
	return literal;
}

char Byte::getValue(){
	return value;
}
