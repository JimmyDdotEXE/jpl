#include <iostream>
#include "Util.h"
#include "value/Bool.h"
#include "value/Logic.h"
#include "value/Comparison.h"
#include "value/Group.h"
#include "value/Negation.h"
#include "parser/Parser.h"
#include "parser/ParseValue.h"
#include "parser/ParseNum.h"
#include "parser/ParseCond.h"


/*
	parseCondDeclaration function
	takes a std::vector<std::string> as a parameter
	creates a new Cond variable and adds it to the current scope
	returns a Cond pointer
*/
Cond *parseCondDeclaration(std::vector<std::string> in){
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
		Bool *var;

		if(in.at(0) == "bool"){
			var = new Bool(in.at(1));
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
	parseCond function
	takes a vector of stirngs as a parameter
	parses a conditional value from the parameter
	returns a Cond pointer
*/
Cond *parseCond(std::vector<std::string> in){

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

							return new Group(parseCond(in));
						}else{
							cont = false;
						}
					}else if(depth == 0){
						throw std::exception();
					}else{
						depth--;
					}
				}
			}
		}
	}else if(in.at(0)[0] == '!'){
		in.at(0) = in.at(0).substr(1);

		return new Negation(parseCond(in));
	}


	//find logical operators && and ||
	//return Logic pointer if any are found
	for(int i=0;i<in.size();i++){
		size_t andPos = in.at(i).find("&&");
		size_t orPos = in.at(i).find("||");

		size_t pos = std::min(andPos, orPos);
		log op;

		if(pos == std::string::npos){
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

		Cond *l = parseCond(lhs);
		Cond *r = parseCond(rhs);

		if(l && r){
			return new Logic(op, l, r);
		}
	}


	//find comparison operators ==, !=, <, >, <=, >=
	//return Comparison pointer if any are found
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

		if(pos == std::string::npos){
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

			if(l && r){
				return new Comparison(op, l, r);
			}
		}else{
			Num *l = parseNum(lhs);
			Num *r = parseNum(rhs);

			if(l && r){
				return new Comparison(op, l, r);
			}
		}
	}

	//if the input is only 1 string long, it's either a variable or a literal
	if(in.size() == 1){
		if(in.at(0) == "True"){
			return new Bool(true);
		}else if(in.at(0) == "False"){
			return new Bool(false);
		}else{
			return dynamic_cast<Cond *>(parseVar(in));
		}
	}

	return NULL;
}
