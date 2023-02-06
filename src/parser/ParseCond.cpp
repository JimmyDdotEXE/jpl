#include <iostream>
#include <algorithm>
#include "Util.h"
#include "statement/Function.h"
#include "value/Bool.h"
#include "value/Logic.h"
#include "value/Comparison.h"
#include "value/Group.h"
#include "value/Negation.h"
#include "parser/Parser.h"
#include "parser/ParseValue.h"
#include "parser/ParseNum.h"
#include "parser/ParseCond.h"


Cond *parseCondFunctionCall(std::vector<std::string> in, bool guaranteedCond){
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

								if(type == "bool"){
									currentFile->addInclusion(func->file);

									name = in.at(0);
									open = true;
									depth++;
									break;
								}else{
									return NULL;
								}
							}else if(guaranteedCond){
								std::cout << "Cond function " + in.at(0) + " undefined." << std::endl;
								throw std::exception();
							}

						}else if(guaranteedCond){
							std::cout << "Cond function " + in.at(0) + " undefined." << std::endl;
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
								std::cout << "missmatched parameter types." << std::endl;
								throw std::exception();
							}
						}

						return new Bool(name, params);						
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
	parseCondDeclaration function
	takes a std::vector<std::string> as a parameter
	creates a new Cond variable and adds it to the current scope
	returns a Cond pointer
*/
Cond *parseCondDeclaration(std::vector<std::string> in){

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
		Bool *var;

		if(in.at(i) == "bool"){
			var = new Bool(in.at(i+1), mut);
		}

		addVar(var);
		return var;
	}else{
		std::cout <<"Undefined type \'" << in.at(i) << "\'." << std::endl;
		throw std::exception();
	}

	return NULL;
}


/*
	parseCond function
	takes a vector of stirngs as a parameter
	parses a conditional value from the parameter
	guaranteedCond tells if the call chain should throw errors. Defaults to true
	tryVar tells if the call chain should try to parse a variable. Defaults to true
	returns a Cond pointer
*/
Cond *parseCond(std::vector<std::string> in, bool guaranteedCond, bool tryVar){

	//find matching () for conditional grouping
	if(in.at(0)[0] == '('){
		int depth = 0;
		bool cont = true;

		for(int i=0;i<in.size() && cont;i++){
			for(int x=0;x<in.at(i).length() && cont;x++){
				if(in.at(i)[x] == '('){
					depth++;
				}else if(in.at(i)[x] == ')'){
					if(depth == 1){
						if(i == in.size()-1 && x == in.at(i).length()-1){
							in.at(0) = in.at(0).substr(1);
							in.back() = in.back().substr(0, in.back().length()-1);

							if(Cond *c = parseCond(in, guaranteedCond)){
								return new Group(c);
							}else{
								return NULL;
							}
						}else{
							cont = false;
						}
					}else if(depth == 0){
						std::cout << "Something went wrong in parseCond()" << std::endl;
						throw std::exception();
					}else{
						depth--;
					}
				}
			}
		}
	}else if(in.at(0)[0] == '!'){
		in.at(0) = in.at(0).substr(1);

		if(Cond *c = parseCond(in, guaranteedCond)){
			return new Negation(c);
		}else{
			return NULL;
		}
	}


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


	//find logical operators && and ||
	//returns a Logic operation if any are found
	for(int i=0;i<in.size();i++){
		size_t andPos = in.at(i).find("&&");
		size_t orPos = in.at(i).find("||");

		size_t pos = std::min(andPos, orPos);
		log op;

		if(pos == std::string::npos || between(matches, i, pos)){
			continue;
		}else if(pos == andPos){
			op = AND;
		}else if(pos == orPos){
			op = OR;
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

		if(in.at(i).substr(pos+2) != ""){
			rhs.insert(rhs.begin(), in.at(i).substr(pos+2));
		}

		Cond *l = parseCond(lhs, guaranteedCond);
		Cond *r = parseCond(rhs, guaranteedCond);

		if(l != NULL && r != NULL){
			return new Logic(op, l, r);
		}else if(l != NULL && guaranteedCond){

			for(int j=0;j<rhs.size();j++){
				std::cout << rhs.at(j) << " ";
			}

			std::cout << "in logic opertaion ";

			for(int j=0;j<in.size();j++){
				std::cout << in.at(j) << " ";
			}

			std::cout << "doesn't have a conditional value." << std::endl;

			throw std::exception();
		}else if(r != NULL && guaranteedCond){

			for(int j=0;j<lhs.size();j++){
				std::cout << lhs.at(j) << " ";
			}

			std::cout << "in logic opertaion ";

			for(int j=0;j<in.size();j++){
				std::cout << in.at(j) << " ";
			}

			std::cout << "doesn't have a conditional value." << std::endl;

			throw std::exception();
		}else if(guaranteedCond){

			for(int j=0;j<lhs.size();j++){
				std::cout << lhs.at(j) << " ";
			}

			std::cout << "and ";

			for(int j=0;j<rhs.size();j++){
				std::cout << rhs.at(j) << " ";
			}

			std::cout << "in logic operation ";

			for(int j=0;j<in.size();j++){
				std::cout << in.at(j) << " ";
			}

			std::cout << "don't have conditional values." << std::endl;

			throw std::exception();
		}
	}


	//find comparison operators ==, !=, <, >, <=, >=
	//returns Comparison if any are found
	for(int i=0;i<in.size();i++){
		size_t eqPos = in.at(i).find("==");
		size_t notEqPos = in.at(i).find("!=");
		size_t lessPos = in.at(i).find("<");
		size_t greatPos = in.at(i).find(">");
		size_t lessEqPos = in.at(i).find("<=");
		size_t greatEqPos = in.at(i).find(">=");

		size_t pos = std::min(std::min(eqPos, notEqPos), std::min(std::min(lessPos, greatPos), std::min(lessEqPos, greatEqPos)));
		int subExtra;
		comp op;

		if(pos == std::string::npos || between(matches, i, pos)){
			continue;
		}else if(pos == eqPos){
			op = EQUAL;
			subExtra = 2;
		}else if(pos == notEqPos){
			op = NOTEQUAL;
			subExtra = 2;
		}else if(pos == lessEqPos){
			op = LESSEQ;
			subExtra = 2;
		}else if(pos == greatEqPos){
			op = GREATEQ;
			subExtra = 2;
		}else if(pos == lessPos){
			op = LESS;
			subExtra = 1;
		}else if(pos == greatPos){
			op = GREAT;
			subExtra = 1;
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

		if(in.at(i).substr(pos+subExtra) != ""){
			rhs.insert(rhs.begin(), in.at(i).substr(pos+subExtra));
		}

		if(op == EQUAL || op == NOTEQUAL){
			Value *l = parseValue(lhs);
			Value *r = parseValue(rhs);

			if(l != NULL && r != NULL){
				return new Comparison(op, l, r);
			}else if(l != NULL && guaranteedCond){

				for(int j=0;j<rhs.size();j++){
					std::cout << rhs.at(j) << " ";
				}

				std::cout << "in comparison ";

				for(int j=0;j<in.size();j++){
					std::cout << in.at(j) << " ";
				}

				std::cout << "doesn't have a value." << std::endl;

				throw std::exception();
			}else if(r != NULL && guaranteedCond){

				for(int j=0;j<lhs.size();j++){
					std::cout << lhs.at(j) << " ";
				}

				std::cout << "in comparison ";

				for(int j=0;j<in.size();j++){
					std::cout << in.at(j) << " ";
				}

				std::cout << "doesn't have a value." << std::endl;

				throw std::exception();
			}else if(guaranteedCond){

				for(int j=0;j<lhs.size();j++){
					std::cout << lhs.at(j) << " ";
				}

				std::cout << "and ";

				for(int j=0;j<rhs.size();j++){
					std::cout << rhs.at(j) << " ";
				}

				std::cout << "in comparison ";

				for(int j=0;j<in.size();j++){
					std::cout << in.at(j) << " ";
				}

				std::cout << "doesn't have a value." << std::endl;

				throw std::exception();
			}
		}else{
			Num *l = parseNum(lhs, guaranteedCond);
			Num *r = parseNum(rhs, guaranteedCond);

			if(l != NULL && r != NULL){
				return new Comparison(op, l, r);
			}else if(l != NULL && guaranteedCond){

				for(int j=0;j<rhs.size();j++){
					std::cout << rhs.at(j) << " ";
				}

				std::cout << "in comparison ";

				for(int j=0;j<in.size();j++){
					std::cout << in.at(j) << " ";
				}

				std::cout << "doesn't have a value." << std::endl;

				throw std::exception();
			}else if(r != NULL && guaranteedCond){

				for(int j=0;j<lhs.size();j++){
					std::cout << lhs.at(j) << " ";
				}

				std::cout << "in comparison ";

				for(int j=0;j<in.size();j++){
					std::cout << in.at(j) << " ";
				}

				std::cout << "doesn't have a value." << std::endl;

				throw std::exception();
			}else if(guaranteedCond){

				for(int j=0;j<lhs.size();j++){
					std::cout << lhs.at(j) << " ";
				}

				std::cout << "and ";

				for(int j=0;j<rhs.size();j++){
					std::cout << rhs.at(j) << " ";
				}

				std::cout << "in comparison ";

				for(int j=0;j<in.size();j++){
					std::cout << in.at(j) << " ";
				}

				std::cout << "doesn't have a value." << std::endl;

				throw std::exception();
			}
		}
	}


	if(Cond *ret = parseCondFunctionCall(in, guaranteedCond)){
		return ret;
	}else if(in.size() == 1){
		if(in.at(0) == "True"){
			return new Bool(true);
		}else if(in.at(0) == "False"){
			return new Bool(false);
		}else if(tryVar){
			return dynamic_cast<Cond *>(parseVar(in));
		}
	}

	return NULL;
}
