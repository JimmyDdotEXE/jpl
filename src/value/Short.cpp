#include "value/Short.h"


Short::Short(){
	literal = false;
	value = 0;
}

Short::Short(short v){
	literal = true;
	value = v;
}

Short::Short(std::string s, mutator m) : Num("short", s, m){
	literal = false;
	value = 0;
}

Short::Short(std::string n, std::vector<Value *> p) : Num("short", n, p){
	literal = false;
	value = 0;
}


bool Short::isLiteral(){
	return literal;
}

short Short::getValue(){
	return value;
}
