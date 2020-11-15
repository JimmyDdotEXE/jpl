#include <iostream>
#include "Util.h"
#include "parser/Parser.h"
#include "parser/ParseNum.h"
#include "parser/ParseCond.h"
#include "parser/ParseText.h"
#include "parser/ParseValue.h"


/*
	parseDeclarationVar function
	takes a std::vector<std::string> as parameter
	parses a variable declaration as a variable
	returns an Value pointer
*/
Value *parseDeclarationVar(std::vector<std::string> in){
	Value *var;

	int typeIndex = 0;

	if(in.size() == 3)
		typeIndex = 1;

	if(in.at(typeIndex) == "byte"){
		return static_cast<Value *>(parseNumDeclaration(in));
	}else if(in.at(typeIndex) == "short"){
		return static_cast<Value *>(parseNumDeclaration(in));
	}else if(in.at(typeIndex) == "int"){
		return static_cast<Value *>(parseNumDeclaration(in));
	}else if(in.at(typeIndex) == "long"){
		return static_cast<Value *>(parseNumDeclaration(in));
	}else if(in.at(typeIndex) == "decimal"){
		return static_cast<Value *>(parseNumDeclaration(in));
	}else if(in.at(typeIndex) == "char"){
		return static_cast<Value *>(parseTextDeclaration(in));
	}else if(in.at(typeIndex) == "string"){
		return static_cast<Value *>(parseTextDeclaration(in));
	}else if(in.at(typeIndex) == "bool"){
		return static_cast<Value *>(parseCondDeclaration(in));
	}

	return NULL;
}


/*
	parseVar function
	takes a std::vector<std::string> as parameter
	parses a variable value
	returns an Value pointer
*/
Value *parseVar(std::vector<std::string> in){
	if(in.size() == 1){
		if(in.at(0).find('\"') != std::string::npos){
			return NULL;
		}

		if(lookupVar(in.at(0))){
			return lookupVar(in.at(0));
		}
	}

	return NULL;
}


/*
	parseValue function
	takes a std::vector<std::string> as parameter
	parses a value
	returns an Value pointer
*/
Value *parseValue(std::vector<std::string> in){
	Value *ret;

	if(ret = static_cast<Value *>(parseNum(in))){
		return ret;
	}else if(ret = static_cast<Value *>(parseCond(in))){
		return ret;
	}else if(ret = static_cast<Value *>(parseText(in))){
		return ret;
	}

	return NULL;
}
