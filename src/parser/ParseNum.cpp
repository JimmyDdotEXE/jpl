#include <cstdlib>
#include <algorithm>
#include <iostream>
#include "Util.h"
#include "statement/Function.h"
#include "value/Byte.h"
#include "value/Short.h"
#include "value/Int.h"
#include "value/Long.h"
#include "value/Decimal.h"
#include "value/Equation.h"
#include "value/Group.h"
#include "value/Negative.h"
#include "parser/Parser.h"
#include "parser/ParseValue.h"
#include "parser/ParseNum.h"

std::vector<std::string> numTypes = {"signed char", "short", "int", "long", "double"};


Num *parseNumFunctionCall(std::vector<std::string> in, bool guaranteedNum){
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

								if(std::find(numTypes.begin(), numTypes.end(), type) != numTypes.end()){
									currentFile->addInclusion(func->file);

									name = in.at(0);
									open = true;
									depth++;
									break;
								}else{
									return NULL;
								}
							}else if(guaranteedNum){
								std::cout << "Num function " + in.at(0) + " undefined." << std::endl;
								throw std::exception();
							}

						}else if(guaranteedNum){
							std::cout << "Num function " + in.at(0) + " undefined." << std::endl;
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

						if(type == "signed char"){
							return new Byte(name, params);
						}else if(type == "short"){
							return new Short(name, params);
						}else if(type == "int"){
							return new Int(name, params);
						}else if(type == "long"){
							return new Long(name, params);
						}else if(type == "double"){
							return new Decimal(name, params);
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
	parseNumDeclaration function
	takes a std::vector<std::string> as a parameter
	creates a new Num variable and adds it to the current scope
	returns a Num pointer
*/
Num *parseNumDeclaration(std::vector<std::string> in){

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
		Num *var;

		if(in.at(i) == "byte"){
			var = new Byte(in.at(i+1), mut);
		}else if(in.at(i) == "short"){
			var = new Short(in.at(i+1), mut);
		}else if(in.at(i) == "int"){
			var = new Int(in.at(i+1), mut);
		}else if(in.at(i) == "long"){
			var = new Long(in.at(i+1), mut);
		}else if(in.at(i) == "decimal"){
			var = new Decimal(in.at(i+1), mut);
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
	parseNum function
	takes a std::vector<std::string> as a parameter
	parses a numerical value from the parameter
	guaranteedNum tells if the call chain should throw errors. Defaults to true
	tryVar tells if the call chain should try to parse a variable. Defaults to true
	returns a Num pointer
*/
Num *parseNum(std::vector<std::string> in, bool guaranteedNum, bool tryVar){

	//find matching () for numeric grouping
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

							if(Num *n = parseNum(in, guaranteedNum)){
								return new Group(n);
							}else{
								return NULL;
							}
						}else{
							cont = false;
						}
					}else if(depth == 0){
						std::cout << "Something went wrong in parseNum()" << std::endl;
						throw std::exception();
					}else{
						depth--;
					}
				}
			}
		}
	}else if(in.at(0)[0] == '-'){
		in.at(0) = in.at(0).substr(1);

		if(Num *n = parseNum(in, guaranteedNum)){
			return new Negative(n);
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


	//find numeric operators + and -
	//returns an Equation if any are found
	for(int i=0;i<in.size();i++){
		size_t addPos = in.at(i).find("+");
		size_t minPos = in.at(i).find("-");

		size_t pos = std::min(addPos, minPos);
		oper op;

		if(pos == std::string::npos || between(matches, i, pos)){
			continue;
		}else if(pos == addPos){
			op = ADD;
		}else if(pos == minPos){
			op = SUB;
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

		Num *l = parseNum(lhs, guaranteedNum);
		Num *r = parseNum(rhs, guaranteedNum);

		if(l != NULL && r != NULL){
			return new Equation(op, l, r);
		}else if(l != NULL && guaranteedNum){

			for(int j=0;j<rhs.size();j++){
				std::cout << rhs.at(j) << " ";
			}

			std::cout << "in equation ";

			for(int j=0;j<in.size();j++){
				std::cout << in.at(j) << " ";
			}

			std::cout << "doesn't have a numeric value." << std::endl;

			throw std::exception();
		}else if(r != NULL && guaranteedNum){

			for(int j=0;j<lhs.size();j++){
				std::cout << lhs.at(j) << " ";
			}

			std::cout << "in equation ";

			for(int j=0;j<in.size();j++){
				std::cout << in.at(j) << " ";
			}

			std::cout << "doesn't have a numeric value." << std::endl;

			throw std::exception();
		}else if(guaranteedNum){

			for(int j=0;j<lhs.size();j++){
				std::cout << lhs.at(j) << " ";
			}

			std::cout << "and ";

			for(int j=0;j<rhs.size();j++){
				std::cout << rhs.at(j) << " ";
			}

			std::cout << "in equation ";

			for(int j=0;j<in.size();j++){
				std::cout << in.at(j) << " ";
			}

			std::cout << "don't have numeric values." << std::endl;

			throw std::exception();
		}
	}


	//find numeric operators *, /, ^, %
	//returns Equation if any are found
	for(int i=0;i<in.size();i++){
		size_t multPos = in.at(i).find("*");
		size_t divPos = in.at(i).find("/");
		size_t powPos = in.at(i).find("^");
		size_t modPos = in.at(i).find("%");

		size_t pos = std::min(std::min(multPos, divPos), std::min(powPos, modPos));
		oper op;

		if(pos == std::string::npos || between(matches, i, pos)){
			continue;
		}else if(pos == multPos){
			op = MULT;
		}else if(pos == divPos){
			op = DIV;
		}else if(pos == powPos){
			op = POW;
		}else if(pos == modPos){
			op = REM;
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

		Num *l = parseNum(lhs, guaranteedNum);
		Num *r = parseNum(rhs, guaranteedNum);

		if(l != NULL && r != NULL){
			return new Equation(op, l, r);
		}else if(l != NULL && guaranteedNum){

			for(int j=0;j<rhs.size();j++){
				std::cout << rhs.at(j) << " ";
			}

			std::cout << "in equation ";

			for(int j=0;j<in.size();j++){
				std::cout << in.at(j) << " ";
			}

			std::cout << "doesn't have a numeric value." << std::endl;

			throw std::exception();
		}else if(r != NULL && guaranteedNum){

			for(int j=0;j<lhs.size();j++){
				std::cout << lhs.at(j) << " ";
			}

			std::cout << "in equation ";

			for(int j=0;j<in.size();j++){
				std::cout << in.at(j) << " ";
			}

			std::cout << "doesn't have a numeric value." << std::endl;

			throw std::exception();
		}else if(guaranteedNum){

			for(int j=0;j<lhs.size();j++){
				std::cout << lhs.at(j) << " ";
			}

			std::cout << "and ";

			for(int j=0;j<rhs.size();j++){
				std::cout << rhs.at(j) << " ";
			}

			std::cout << "in equation ";

			for(int j=0;j<in.size();j++){
				std::cout << in.at(j) << " ";
			}

			std::cout << "don't have numeric values." << std::endl;

			throw std::exception();
		}
	}


	if(Num *ret = parseNumFunctionCall(in, guaranteedNum)){
		return ret;
	}else if(in.size() == 1){
		if(numeric(in.at(0))){
			if(in.at(0).find('.') != std::string::npos){
				return new Decimal(strtod(in.at(0).c_str(), NULL));
			}else{
				return new Long(atoi(in.at(0).c_str()));
			}
		}else if(tryVar){
			return dynamic_cast<Num *>(parseVar(in));
		}
	}

	return NULL;
}
