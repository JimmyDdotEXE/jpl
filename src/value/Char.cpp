#include "value/Char.h"


Char::Char(){
	literal = false;
	value = '\0';
}

Char::Char(char c, bool esc){
	literal = true;
	value = c;
	escape = esc;
}

Char::Char(std::string s, mutator m) : Text("char", s, m){
	literal = false;
	value = '\0';
}

Char::Char(std::string n, std::vector<Value *> p) : Text("char", n, p){
	literal = false;
	value = '\0';
}


bool Char::isLiteral(){
	return literal;
}

char Char::getValue(){
	return value;
}

bool Char::getEscape(){
	return escape;
}
