#include "value/Int.h"


Int::Int(){
	literal = false;
	value = 0;
}

Int::Int(int v){
	literal = true;
	value = v;
}

Int::Int(std::string s) : Num("int", s){
	literal = false;
	value = 0;
}


bool Int::isLiteral(){
	return literal;
}

int Int::getValue(){
	return value;
}
