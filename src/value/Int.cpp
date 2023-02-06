#include "value/Int.h"


Int::Int(){
	literal = false;
	value = 0;
}

Int::Int(int v){
	literal = true;
	value = v;
}

Int::Int(std::string s, mutator m) : Num("int", s, m){
	literal = false;
	value = 0;
}

Int::Int(std::string n, std::vector<Value *> p) : Num("int", n, p){
	literal = false;
	value = 0;
}


bool Int::isLiteral(){
	return literal;
}

int Int::getValue(){
	return value;
}
