#include "value/Short.h"


Short::Short(){
	literal = false;
	value = 0;
}

Short::Short(short v){
	literal = true;
	value = v;
}

Short::Short(std::string s) : Num("short", s){
	literal = false;
	value = 0;
}


bool Short::isLiteral(){
	return literal;
}

short Short::getValue(){
	return value;
}
