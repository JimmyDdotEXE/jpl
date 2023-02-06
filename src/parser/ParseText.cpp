#include <iostream>
#include <algorithm>
#include "Util.h"
#include "statement/Function.h"
#include "parser/Parser.h"
#include "value/Char.h"
#include "value/String.h"
#include "value/Concatenation.h"
#include "parser/ParseValue.h"
#include "parser/ParseText.h"


Text *parseTextFunctionCall(std::vector<std::string> in, bool guaranteedText, bool str){
	bool open = false;
	int depth = 0;

	Function *func;

	std::string type;
	std::string name;
	std::vector<Value *> params;
	std::vector<std::string> holder;

	for(int i=0;i<in.size();i++){
		size_t recent = 0;

		while(1){
			size_t openPos = in.at(i).find('(', recent);
			size_t closePos = in.at(i).find(')', recent);
			size_t commaPos = in.at(i).find(',', recent);

			size_t pos = std::min(std::min(openPos, closePos), commaPos);

			if(pos != std::string::npos){
				if(pos == openPos){
					if(!open){
						if(in.at(i).length() == 1){
							in.erase(in.begin()+i);
							i--;
							break;
						}else if(in.at(i).substr(0, pos) == ""){
							in.at(i) = in.at(i).substr(pos+1);
						}else if(in.at(i).substr(pos+1) == ""){
							in.at(i) = in.at(i).substr(0, pos);
						}else{
							in.insert(in.begin()+i+1, in.at(i).substr(pos+1));
							in.at(i) = in.at(i).substr(0, pos);
						}


						func = lookupFunction(in.at(0));

						if(func != NULL){
							if(func->file != NULL){
								type = func->getType();

								if(type == "string" && str || type == "char" && !str){
									currentFile->addInclusion(func->file);

									name = in.at(0);
									open = true;
									depth++;
									break;
								}else{
									return NULL;
								}
							}else{
								std::cout << "Function " + in.at(0) + " undefined.\n";
								throw std::exception();
							}
						}else{
							std::cout << "Function " + in.at(0) + " undefined.\n";
							throw std::exception();
						}
					}

					depth++;
				}else if(pos == closePos){
					if(open && depth == 1){
						if(in.at(i).length() == 1){
							in.erase(in.begin()+i);
							i--;
						}else if(in.at(i).substr(0, pos) == ""){
							in.at(i) = in.at(i).substr(pos+1);
							i--;
						}else if(in.at(i).substr(pos+1) == ""){
							in.at(i) = in.at(i).substr(0, pos);
							holder.push_back(in.at(i));
						}else{
							in.insert(in.begin()+i+1, in.at(i).substr(pos+1));
							in.at(i) = in.at(i).substr(0, pos);
							holder.push_back(in.at(i));
						}

						if(Value *v = parseValue(holder)){
							params.push_back(v);
						}

						std::vector<Value *> matchParams = func->getParameters();
						for(int x=0;x<params.size() && x<matchParams.size();x++){
							if(!typeCheck(params.at(x), matchParams.at(x))){
								std::cout << "missmatched parameter types.\n";
								throw std::exception();
							}
						}

						if(type == "string"){
							return new String(name, params);
						}else if(type == "char"){
							return new Char(name, params);
						}
					}

					depth--;
				}else if(pos == commaPos){
					if(open && depth == 1){
						if(in.at(i).length() == 1){
							in.erase(in.begin()+i);
							i--;
						}else if(in.at(i).substr(0, pos) == ""){
							in.at(i) = in.at(i).substr(pos+1);
							i--;
						}else if(in.at(i).substr(pos+1) == ""){
							in.at(i) = in.at(i).substr(0, pos);
							holder.push_back(in.at(i));
						}else{
							in.insert(in.begin()+i+1, in.at(i).substr(pos+1));
							in.at(i) = in.at(i).substr(0, pos);
							holder.push_back(in.at(i));
						}

						params.push_back(parseValue(holder));
						holder.clear();
						break;
					}
				}

				recent = pos+1;
			}else{
				holder.push_back(in.at(i));
				break;
			}
		}
	}

	return NULL;
}


/*
	parseTextDeclaration function
	takes a std::vector<std::string> as a parameter
	creates a new Text variable and adds it to the current scope
	returns a Text pointer
*/
Text *parseTextDeclaration(std::vector<std::string> in){
	mutator mut = mut_NONE;

	int i;
	for(i=0;i<in.size();i++){
		if(in.at(i) == "global"){
			mut = mut | mut_GLOBAL;
		}else if(in.at(i) == "const"){
			mut = mut | mut_CONST;
		}else if(in.at(i) == "static"){
			mut = mut | mut_STATIC;
		}else{
			break;
		}
	}

	nameCheck(in.at(i+1));

	if(lookupVar(in.at(i+1))){
		std::cout << in.at(i+1) + " Redefined." << std::endl;
		throw std::exception();
	}else if(lookupType(in.at(i))){

		Text *var;

		if(in.at(i) == "char"){
			var = new Char(in.at(i+1), mut);
		}else if(in.at(i) == "string"){
			var = new String(in.at(i+1), mut);
		}

		addVar(var);
		return var;
	}else{
		std::cout << in.at(i) + " Undefined Type." << std::endl;
		throw std::exception();
	}

	return NULL;
}


/*
	parseString function
	takes a std::vector<std::string> as a parameter
	parses a string value from the parameter
	guaranteedText tells if the call chain should throw errors. Defaults to true
	tryVar tells if the call chain should try to parse a variable. Defaults to true
	returns a String pointer
*/
String *parseString(std::vector<std::string> in, bool guaranteedText, bool tryVar){
	std::vector<pair_t> matches;

	int depth = 0;
	for(int i=0;i<in.size();i++){
		size_t mostRecent = std::string::npos;

		while(1){
			size_t openPos = in.at(i).find("(", mostRecent+1);
			size_t closePos = in.at(i).find(")", mostRecent+1);

			size_t pos = std::min(openPos, closePos);

			if(pos == std::string::npos){
				break;
			}else if(pos == openPos){
				matches.push_back({i, pos, -1, std::string::npos});

				depth++;
			}else if(pos == closePos){
				for(int x=matches.size()-1;x>=0;x--){
					if(matches.at(x).closeStr == -1){
						matches.at(x).closeStr = i;
						matches.at(x).closePos = pos;

						break;
					}
				}

				depth--;
			}

			mostRecent = pos;
		}
	}


	for(int i=0;i<in.size();i++){
		size_t pos = in.at(i).find("+");

		if(pos == std::string::npos || between(matches, i, pos)){
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


		Text *l = parseText(lhs, guaranteedText);
		Text *r = parseText(rhs, guaranteedText);


		if(l != NULL && r != NULL){
			return new Concatenation(l, r);
		}else if(l != NULL && guaranteedText){

			for(int j=0;j<rhs.size();j++){
				std::cout << rhs.at(j) << " ";
			}

			std::cout << "in concatenation ";

			for(int j=0;j<in.size();j++){
				std::cout << in.at(j) << " ";
			}

			std::cout << "doesn't have a text value." << std::endl;

			throw std::exception();
		}else if(r != NULL && guaranteedText){

			for(int j=0;j<lhs.size();j++){
				std::cout << lhs.at(j) << " ";
			}

			std::cout << "in concatenation ";

			for(int j=0;j<in.size();j++){
				std::cout << in.at(j) << " ";
			}

			std::cout << "doesn't have a text value." << std::endl;

			throw std::exception();
		}else if(guaranteedText){

			for(int j=0;j<lhs.size();j++){
				std::cout << lhs.at(j) << " ";
			}

			std::cout << "and ";

			for(int j=0;j<rhs.size();j++){
				std::cout << rhs.at(j) << " ";
			}

			std::cout << "in concatenation ";

			for(int j=0;j<in.size();j++){
				std::cout << in.at(j) << " ";
			}

			std::cout << "don't have text values." << std::endl;

			throw std::exception();
		}
	}


	if(String *ret = dynamic_cast<String *>(parseTextFunctionCall(in, guaranteedText, true))){
		return ret;
	}else if(in.size() == 1){
		if(in.at(0)[0] == '\"' && in.at(0)[in.at(0).length()-1] == '\"'){
			return new String(in.at(0).substr(1, in.at(0).length()-2).c_str());
		}else if(tryVar){
			return dynamic_cast<String *>(parseVar(in));
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
Char *parseChar(std::vector<std::string> in, bool guaranteedText, bool tryVar){
	if(Char *ret = dynamic_cast<Char *>(parseTextFunctionCall(in, guaranteedText, false))){
		return ret;
	}else if(in.size() == 1){
		if(in.at(0)[0] == '\'' && in.at(0)[in.at(0).length()-1] == '\''){
			if(in.at(0).length() == 3){
				return new Char(in.at(0)[1]);
			}else if(in.at(0).length() == 4 && in.at(0)[1] == '\\'){
				return new Char(in.at(0)[2], true);
			}
		}else if(tryVar){
			return dynamic_cast<Char *>(parseVar(in));
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
Text *parseText(std::vector<std::string> in, bool guaranteedText, bool tryVar){
	Text *text = parseChar(in, guaranteedText, tryVar);

	if(text){
		return text;
	}else{
		return parseString(in, guaranteedText, tryVar);
	}
}
