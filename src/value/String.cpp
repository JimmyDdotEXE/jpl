#include "value/String.h"


String::String(){
	literal = false;
	value = "";
}

String::String(const char *s){
	literal = true;
	value = std::string(s);
}

String::String(std::string n) : Text("std::string", n){
	literal = false;
	value = "";
}


bool String::isLiteral(){
	return literal;
}

std::string String::getValue(){
	return value;
}
