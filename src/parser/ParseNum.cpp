#include <cstdlib>
#include <iostream>
#include "Util.h"
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


/*
	parseNumDeclaration function
	takes a std::vector<std::string> as a parameter
	creates a new Num variable and adds it to the current scope
	returns a Num pointer
*/
Num *parseNumDeclaration(std::vector<std::string> in){
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

		Num *var;

		if(in.at(0) == "byte"){
			var = new Byte(in.at(1));
		}else if(in.at(0) == "short"){
			var = new Short(in.at(1));
		}else if(in.at(0) == "int"){
			var = new Int(in.at(1));
		}else if(in.at(0) == "long"){
			var = new Long(in.at(1));
		}else if(in.at(0) == "decimal"){
			var = new Decimal(in.at(1));
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
	parseNum function
	takes a std::vector<std::string> as a parameter
	parses a numerical value from the parameter
	returns a Num pointer
*/
Num *parseNum(std::vector<std::string> in){
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

							return new Group(parseNum(in));
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
	}else if(in.at(0)[0] == '-'){
		in.at(0) = in.at(0).substr(1);

		return new Negative(parseNum(in));
	}

				
	for(int i=0;i<in.size();i++){
		size_t addPos = in.at(i).find("+");
		size_t minPos = in.at(i).find("-");

		size_t pos = std::min(addPos, minPos);
		oper op;

		if(pos == std::string::npos){
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

		Num *l = parseNum(lhs);
		Num *r = parseNum(rhs);

		if(l && r){
			return new Equation(op, l, r);
		}
	}

	for(int i=0;i<in.size();i++){
		size_t multPos = in.at(i).find("*");
		size_t divPos = in.at(i).find("/");
		size_t powPos = in.at(i).find("^");
		size_t modPos = in.at(i).find("%");

		size_t pos = std::min(std::min(multPos, divPos), std::min(powPos, modPos));
		oper op;

		if(pos == std::string::npos){
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

		Num *l = parseNum(lhs);
		Num *r = parseNum(rhs);

		if(l && r){
			return new Equation(op, l, r);
		}
	}


	if(in.size() == 1){
		if(numeric(in.at(0))){
			if(in.at(0).find('.') != std::string::npos){
				return new Decimal(strtod(in.at(0).c_str(), NULL));
			}else{
				return new Long(atoi(in.at(0).c_str()));
			}
		}else{
			return dynamic_cast<Num *>(parseVar(in));
		}
	}

	return NULL;
}
