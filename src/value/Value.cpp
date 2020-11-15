#include "value/Value.h"


Value::~Value(){}

Value::Value(){
	var = false;
	type = "";
	name = "";
}

Value::Value(std::string t, std::string n){
	var = true;
	type = t;
	name = n;
}


bool Value::isVar(){
	return var;
}


std::string Value::getType(){
	return type;
}

std::string Value::getName(){
	return name;
}
