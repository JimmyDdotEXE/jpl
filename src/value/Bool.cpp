#include "value/Bool.h"


Bool::Bool(){
	literal = false;
	value = false;
}

Bool::Bool(bool v){
	literal = true;
	value = v;
}

Bool::Bool(std::string s) : Cond("bool", s){
	literal = false;
	value = false;
}


bool Bool::isLiteral(){
	return literal;
}

bool Bool::getValue(){
	return value;
}
