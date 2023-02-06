#include "value/Value.h"
#include "File.h"


Value::~Value(){}

Value::Value(){
	var = false;
	funcCall = false;
	type = "";
	name = "";

	file = NULL;

	mut = mut_NONE;
}

Value::Value(std::string t, std::string n, mutator m){
	var = true;
	funcCall = false;
	type = t;
	name = n;

	file = NULL;

	mut = m;
}

Value::Value(std::string t, std::string n, std::vector<Value *> p){
	var = false;
	funcCall = true;
	type = t;
	name = n;
	parameters = p;

	file = NULL;

	mut = mut_NONE;
}


bool Value::isVar(){
	return var;
}

bool Value::isFuncCall(){
	return funcCall;
}


mutator Value::getMutator(){
	return mut;
}

std::string Value::getType(){
	return type;
}

std::string Value::getName(){
	return name;
}

std::vector<Value *> Value::getParameters(){
	return parameters;
}

File *Value::getFile(){
	return file;
}


bool Value::setFile(File *f){
	file = f;

	return file == f;
}




mutator operator |(mutator const& l, mutator const& r){
	return static_cast<mutator>(static_cast<unsigned>(l) | static_cast<unsigned>(r));
}
