#include <iostream>
#include "Util.h"
#include "parser/Parser.h"
#include "value/Char.h"
#include "value/String.h"
#include "value/Concatenation.h"
#include "parser/ParseValue.h"
#include "parser/ParseText.h"


/*
	parseTextDeclaration function
	takes a std::vector<std::string> as a parameter
	creates a new Text variable and adds it to the current scope
	returns a Text pointer
*/
Text *parseTextDeclaration(std::vector<std::string> in){
	if(in.at(1) == "loop"){
		std::cout << "Name \'loop\' is reserved." << std::endl;

		throw std::exception();
	}else if(size_t pos = in.at(1).find("loop") != std::string::npos){
		if(numeric(in.at(1).substr(pos+4))){
			std::cout << "Name \'" << in.at(1) << "\' is reserved." << std::endl;

			throw std::exception();
		}
	}

	if(lookupVar(in.at(1))){
		std::cout << in.at(1) + " Redefined." << std::endl;

		throw std::exception();
	}else if(lookupType(in.at(0))){

		Text *var;

		if(in.at(0) == "char"){
			var = new Char(in.at(1));
		}else if(in.at(0) == "string"){
			var = new String(in.at(1));
		}

		addVar(var);
		return var;

	}else{
		std::cout << in.at(0) + " Undefined Type." << std::endl;

		throw std::exception();
	}

	return NULL;
}


/*
	parseString function
	takes a std::vector<std::string> as a parameter
	parses a string value from the parameter
	returns a String pointer
*/
String *parseString(std::vector<std::string> in){
	for(int i=0;i<in.size();i++){
		size_t pos = in.at(i).find("+");

		if(pos == std::string::npos){
			continue;
		}else if(in.at(i)[0] == '\'' || in.at(i)[0] == '\"'){
			continue;
		}

		std::vector<std::string> lhs;
		std::vector<std::string> rhs;

		for(int x=0;x<in.size();x++){
			if(x<i){
				lhs.push_back(in.at(x));
			}else if(x>i){
				rhs.push_back(in.at(x));
			}
		}

		if(in.at(i).substr(0, pos) != ""){
			lhs.push_back(in.at(i).substr(0, pos));
		}

		if(in.at(i).substr(pos+1) != ""){
			rhs.insert(rhs.begin(), in.at(i).substr(pos+1));
		}

		return new Concatenation(parseText(lhs), parseText(rhs));
	}

	if(in.size() == 1){
		if(Value *var = parseVar(in)){
			return dynamic_cast<String *>(var);
		}else{
			return new String(in.at(0).substr(1, in.at(0).length()-2).c_str());
		}
	}

	return NULL;
}


/*
	parseChar function
	takes a std::vector<std::string> as a parameter
	parses a character value from the parameter
	returns a Char pointer
*/
Char *parseChar(std::vector<std::string> in){
	if(in.size() == 1){
		if(Value *var = parseVar(in)){
			return dynamic_cast<Char *>(var);
		}else if(in.at(0)[0] == '\'' && in.at(0)[in.at(0).length()-1] == '\''){
			if(in.at(0).length() == 3){
				return new Char(in.at(0)[1]);
			}else if(in.at(0).length() == 4 && in.at(0)[1] == '\\'){
				return new Char(in.at(0)[2], true);
			}
		}
	}

	return NULL;
}


/*
	parseText function
	takes a std::vector<std::string> as a parameter
	parses a text value from the parameter
	returns a Text pointer
*/
Text *parseText(std::vector<std::string> in){
	Text *text = parseChar(in);

	if(text){
		return text;
	}else{
		return parseString(in);
	}
}
