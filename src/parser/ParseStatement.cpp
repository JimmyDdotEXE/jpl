#include "statement/Print.h"
#include "statement/Assignment.h"
#include "value/Int.h"
#include "value/Bool.h"
#include "value/Char.h"
#include "value/String.h"
#include "parser/ParseNum.h"
#include "parser/ParseCond.h"
#include "parser/ParseText.h"
#include "parser/ParseValue.h"
#include "parser/ParseStatement.h"


/*
	parseDeclarationStatement function
	takes a std::vector<std::string> as parameter
	parses a variable declaration and sets it equal to base value
	returns an Assignment pointer
*/
Assignment *parseDeclarationStatement(std::vector<std::string> in){
	Value *var;

	int typeIndex = 0;

	if(in.size() == 3)
		typeIndex = 1;

	//parse a byte declaration
	if(in.at(typeIndex) == "byte"){
		if(var = parseNumDeclaration(in)){
			return new Assignment(ASSIGN, var, new Int(0));
		}

	//parse a short declaration
	}else if(in.at(typeIndex) == "short"){
		if(var = parseNumDeclaration(in)){
			return new Assignment(ASSIGN, var, new Int(0));
		}

	//parse an int declaration
	}else if(in.at(typeIndex) == "int"){
		if(var = parseNumDeclaration(in)){
			return new Assignment(ASSIGN, var, new Int(0));
		}

	//parse a long declaration
	}else if(in.at(typeIndex) == "long"){
		if(var = parseNumDeclaration(in)){
			return new Assignment(ASSIGN, var, new Int(0));
		}

	//parse a decimal declaration
	}else if(in.at(typeIndex) == "decimal"){
		if(var = parseNumDeclaration(in)){
			return new Assignment(ASSIGN, var, new Int(0));
		}

	//parse a char declaration
	}else if(in.at(typeIndex) == "char"){
		if(var = parseTextDeclaration(in)){
			return new Assignment(ASSIGN, var, new Char('\0'));
		}

	//parse a string declaration
	}else if(in.at(typeIndex) == "string"){
		if(var = parseTextDeclaration(in)){
			std::string temp = "";
			return new Assignment(ASSIGN, var, new String(temp.c_str()));
		}

	//parse a bool declaration
	}else if(in.at(typeIndex) == "bool"){
		if(var = parseCondDeclaration(in)){
			return new Assignment(ASSIGN, var, new Bool(false));
		}
	}

	return NULL;
}


/*
	parseStatement function
	takes a std::vector<std::string> as parameter
	parses a statement from the parameter
	returns a Statement pointer
*/
Statement *parseStatement(std::vector<std::string> in){

	//parse a print statement and return a Print pointer
	if(in.size()){
		if(in.at(0) == "print"){
			in.erase(in.begin());
			return new Print(parseValue(in));
		}
	}

	//find any assignment ops and return Assignment pointer
	for(int i=0;i<in.size();i++){
		size_t eqPos = in.at(i).find("=");
		size_t addPos = in.at(i).find("+=");
		size_t subPos = in.at(i).find("-=");
		size_t multPos = in.at(i).find("*=");
		size_t divPos = in.at(i).find("/=");

		size_t pos = std::min(eqPos, std::min(std::min(addPos, subPos), std::min(multPos, divPos)));
		int subExtra;
		assign op;

		if(pos == std::string::npos){
			continue;
		}else if(pos == eqPos){
			op = ASSIGN;
			subExtra = 1;
		}else if(pos == addPos){
			op = ADDASSIGN;
			subExtra = 2;
		}else if(pos == subPos){
			op = SUBASSIGN;
			subExtra = 2;
		}else if(pos == multPos){
			op = MULTASSIGN;
			subExtra = 2;
		}else if(pos == divPos){
			op = DIVASSIGN;
			subExtra = 2;
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

		Value *var = parseVar(lhs);
		if(!var){
			var = parseDeclarationVar(lhs);
		}

		Value *val = parseValue(rhs);


		//if operator is normal assignment op
		if(op == ASSIGN){
			//only Num types can be assigned to Num types
			if(Num *l = dynamic_cast<Num *>(var)){
				if(Num *r = dynamic_cast<Num *>(val)){
					return new Assignment(op, var, val);
				}

			//only Cond types can be assigned to Cond types
			}else if(Cond *l = dynamic_cast<Cond *>(var)){
				if(Cond *r = dynamic_cast<Cond *>(val)){
					return new Assignment(op, var, val);
				}

			//only String types can be assigned to String types
			}else if(String *l = dynamic_cast<String *>(var)){
				if(String *r = dynamic_cast<String *>(val)){
					return new Assignment(op, var, val);
				}

			//only Char types can be assigned to Char types
			}else if(Char *l = dynamic_cast<Char *>(var)){
				if(Char *r = dynamic_cast<Char *>(val)){
					return new Assignment(op, var, val);
				}
			}

		//if operator is an add assignment op
		}else if(op == ADDASSIGN){
			//only Num types can be add assigned to Num types
			if(Num *l = dynamic_cast<Num *>(var)){
				if(Num *r = dynamic_cast<Num *>(val)){
					return new Assignment(op, var, val);
				}

			//only Text types can be add assigned to String types
			}else if(String *l = dynamic_cast<String *>(var)){
				if(Text *r = dynamic_cast<Text *>(val)){
					return new Assignment(op, var, val);
				}
			}

		//if operator is any other assignment op
		}else{
			//only Num types can be assigned to Num types using arithmetic assignment ops
			if(Num *l = dynamic_cast<Num *>(var)){
				if(Num *r = dynamic_cast<Num *>(val)){
					return new Assignment(op, var, val);
				}
			}
		}


		throw std::exception();
	}


	//if the input is 2 strings long call parseDeclarationStatement()
	if(in.size() == 2){
		return parseDeclarationStatement(in);
	}

	return NULL;
}
