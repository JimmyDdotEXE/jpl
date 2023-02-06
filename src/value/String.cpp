#include "value/String.h"


String::String(){
	literal = false;
	value = "";
}

String::String(const char *s){
	literal = true;
	value = std::string(s);
}

String::String(std::string n, mutator m) : Text("std::string", n, m){
	literal = false;
	value = "";
}

String::String(std::string n, std::vector<Value *> p) : Text("std::string", n, p){
	literal = false;
	value = "";
}


bool String::isLiteral(){
	return literal;
}

std::string String::getValue(){
	return value;
}
