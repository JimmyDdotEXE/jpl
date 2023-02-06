#include <iostream>
#include "Util.h"
#include "parser/Parser.h"
#include "parser/ParseNum.h"
#include "parser/ParseCond.h"
#include "parser/ParseText.h"
#include "parser/ParseStatement.h"
#include "parser/ParseValue.h"


std::vector<global_t> parseGlobals(std::vector<std::string> *in){
	std::vector<global_t> ret;
	std::vector<std::string> comments;


	//read next line from file
	for(int j=0;j < in->size();j++){
		std::string line = in->at(j);
		std::string comment = "";

		//look for a comment in the current line
		size_t cPos = line.find('#');
		if(cPos != std::string::npos){
			comment = line.substr(cPos+1);
			line = line.substr(0, cPos);
		}

		bool globalFound = line.find("global") != std::string::npos;

		int numTabs = 0;
		//count the tab depth of the line
		for(int i=0;line[i] == '\t';i++){
			numTabs++;
		}

		if(globalFound && numTabs != 0){
			std::cout << "globals cannot be defined within statements or functions." << std::endl;
			throw std::exception();
		}


		//split the line into strings separated by tabs
		std::vector<std::string> temp = splitString(line, '\t');
		std::vector<std::string> ss;

		//if there were any strings resulting from the last split
		if(temp.size()){
			//split the first string again by spaces this time
			ss = splitString(temp.at(0), ' ');
		}

		/*
		 * due to how these two calls to splitString() are used,
		 * the language requires tabs instead of spaces for indentation
		 * and tabs should not be used in the main statement of the line
		 * tabs are safe to use in comments and to separate a comment from a statement
		 */


		if(ss.size() == 0 && comment == ""){
			comments.clear();
			continue;
		}else if(ss.size() == 0 && comment != ""){
			comments.push_back(comment);
			continue;
		}if(!globalFound){
			continue;
		}


		Statement *state;
		if(state = parseStatement(ss)){
			if(Assignment *assign = dynamic_cast<Assignment *>(state)){
				if(assign->getOp() == ASSIGN && assign->getLeft()->getMutator() & mut_GLOBAL){

					in->erase(in->begin()+j-comments.size(), in->begin()+j+1);
					j -= comments.size()+1;

					global_t g = {assign, comment, comments};
					ret.push_back(g);

					comments.clear();
				}
			}
		}
	}

	return ret;
}


/*
	parseDeclarationVar function
	takes a std::vector<std::string> as parameter
	parses a variable declaration as a variable
	returns an Value pointer
*/
Value *parseDeclarationVar(std::vector<std::string> in){
	if(in.size() < 2){
		return NULL;
	}

	int typeIndex = in.size() - 2;

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
		}else if(in.at(0).find('\'') != std::string::npos){
			return NULL;
		}

		if(Value *var = lookupVar(in.at(0))){
			if(var->getMutator() & mut_GLOBAL){
				currentFile->addInclusion(var->getFile());
			}

			return var;
		}else{
			std::cout << "Variable " << in.at(0) << " undefined in this scope." << std::endl;
			throw std::exception();
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
	if(in.size() == 0){
		return NULL;
	}

	Value *ret;

	if(ret = static_cast<Value *>(parseNum(in, false, false))){
		return ret;
	}else if(ret = static_cast<Value *>(parseCond(in, false, false))){
		return ret;
	}else if(ret = static_cast<Value *>(parseText(in, false))){
		return ret;
	}else if(ret = parseVar(in)){
		return ret;
	}

	return NULL;
}
