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

Char::Char(std::string s) : Text("char", s){
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
