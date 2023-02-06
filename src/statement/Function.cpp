#include "statement/Function.h"


Function::Function(){}

Function::Function(std::string t, std::string n, std::vector<Value *> p){
	setType(t);
	name = n;
	parameters = p;

	file = NULL;
}


std::string Function::getType(){
	return type;
}

std::string Function::getName(){
	return name;
}

std::vector<Value *> Function::getParameters(){
	return parameters;
}

std::vector<line_t> Function::getBody(){
	return body;
}

std::vector<std::string> Function::getTemp(){
	return temp;
}

std::string Function::getSideComment(){
	return sideComment;
}

std::vector<std::string> Function::getTopComment(){
	return topComment;
}


void Function::setType(std::string t){
	if(t == "none"){
		type = "void";
	}else if(t == "byte"){
		type = "signed char";
	}else if(t == "decimal"){
		type = "double";
	}else if(t == "string"){
		type = "std::string";
	}else{
		type = t;
	}
}

void Function::setName(std::string n){
	name = n;
}

void Function::setParameters(std::vector<Value *> p){
	parameters = p;
}

void Function::setBody(std::vector<line_t> b){
	body = b;
}

void Function::setTemp(std::vector<std::string> t){
	temp = t;
}

bool Function::setSideComment(std::string comment){
	sideComment = comment;

	return sideComment == comment;
}

bool Function::setTopComment(std::vector<std::string> comment){
	topComment = comment;

	return topComment == comment;
}


void Function::addLine(line_t l){
	body.push_back(l);
}
