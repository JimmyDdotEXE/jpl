#include "value/Bool.h"


Bool::Bool(){
	literal = false;
	value = false;
}

Bool::Bool(bool v){
	literal = true;
	value = v;
}

Bool::Bool(std::string s, mutator m) : Cond("bool", s, m){
	literal = false;
	value = false;
}

Bool::Bool(std::string n, std::vector<Value *> p) : Cond("bool", n, p){
	literal = false;
	value = false;
}


bool Bool::isLiteral(){
	return literal;
}

bool Bool::getValue(){
	return value;
}
