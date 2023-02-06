#include <iostream>
#include "Util.h"
#include "statement/NoneCall.h"
#include "statement/Print.h"
#include "statement/Return.h"
#include "statement/Assignment.h"
#include "statement/Function.h"
#include "value/Int.h"
#include "value/Bool.h"
#include "value/Char.h"
#include "value/String.h"
#include "parser/Parser.h"
#include "parser/ParseNum.h"
#include "parser/ParseCond.h"
#include "parser/ParseText.h"
#include "parser/ParseValue.h"
#include "parser/ParseStatement.h"


NoneCall *parseNoneCall(std::vector<std::string> in){
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

								if(type == "void"){
									currentFile->addInclusion(func->file);

									name = in.at(0);
									open = true;
									depth++;
									break;
								}else{
									return NULL;
								}
							}else if(lookupVar(in.at(0)) == NULL){
								std::cout << "Function " + in.at(0) + " undefined.\n";
								throw std::exception();
							}

						}else if(lookupVar(in.at(0)) == NULL){
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


						return new NoneCall(name, params);
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
	parseDeclarationStatement function
	takes a std::vector<std::string> as parameter
	parses a variable declaration and sets it equal to base value
	returns an Assignment pointer
*/
Assignment *parseDeclarationStatement(std::vector<std::string> in){
	Value *var;

	if(in.size() < 2){
		return NULL;
	}

	int typeIndex = in.size() - 2;


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
		if(var == NULL){
			var = parseDeclarationVar(lhs);
		}else if(var->getMutator() & mut_CONST){
			std::cout << "Cannot reassign constant variable " << var->getName() << "." << std::endl;

			throw std::exception();
		}

		Value *val = parseValue(rhs);


		//if operator is normal assignment op
		if(op == ASSIGN){
			//only Num types can be assigned to Num types
			if(Num *l = dynamic_cast<Num *>(var)){
				if(Num *r = dynamic_cast<Num *>(val)){
					return new Assignment(op, var, val);
				}else{

					for(int j=0;j<rhs.size();j++){
						std::cout << rhs.at(j) << " ";
					}

					std::cout << "in assignment ";

					for(int j=0;j<in.size();j++){
						std::cout << in.at(j) << " ";
					}

					std::cout << "doesn't have a numeric value." << std::endl;

					throw std::exception();
				}

			//only Cond types can be assigned to Cond types
			}else if(Cond *l = dynamic_cast<Cond *>(var)){
				if(Cond *r = dynamic_cast<Cond *>(val)){
					return new Assignment(op, var, val);
				}else{

					for(int j=0;j<rhs.size();j++){
						std::cout << rhs.at(j) << " ";
					}

					std::cout << "in assignment ";

					for(int j=0;j<in.size();j++){
						std::cout << in.at(j) << " ";
					}

					std::cout << "doesn't have a cond value." << std::endl;

					throw std::exception();
				}

			//only String types can be assigned to String types
			}else if(String *l = dynamic_cast<String *>(var)){
				if(String *r = dynamic_cast<String *>(val)){
					return new Assignment(op, var, val);
				}else{

					for(int j=0;j<rhs.size();j++){
						std::cout << rhs.at(j) << " ";
					}

					std::cout << "in assignment ";

					for(int j=0;j<in.size();j++){
						std::cout << in.at(j) << " ";
					}

					std::cout << "doesn't have a string value." << std::endl;

					throw std::exception();
				}

			//only Char types can be assigned to Char types
			}else if(Char *l = dynamic_cast<Char *>(var)){
				if(Char *r = dynamic_cast<Char *>(val)){
					return new Assignment(op, var, val);
				}else{

					for(int j=0;j<rhs.size();j++){
						std::cout << rhs.at(j) << " ";
					}

					std::cout << "in assignment ";

					for(int j=0;j<in.size();j++){
						std::cout << in.at(j) << " ";
					}

					std::cout << "doesn't have a character value." << std::endl;

					throw std::exception();
				}
			}

		//if operator is an add assignment op
		}else if(op == ADDASSIGN){
			//only Num types can be add assigned to Num types
			if(Num *l = dynamic_cast<Num *>(var)){
				if(Num *r = dynamic_cast<Num *>(val)){
					return new Assignment(op, var, val);
				}else{

					for(int j=0;j<rhs.size();j++){
						std::cout << rhs.at(j) << " ";
					}

					std::cout << "in assignment ";

					for(int j=0;j<in.size();j++){
						std::cout << in.at(j) << " ";
					}

					std::cout << "doesn't have a numeric value." << std::endl;

					throw std::exception();
				}

			//only Text types can be add assigned to String types
			}else if(String *l = dynamic_cast<String *>(var)){
				if(Text *r = dynamic_cast<Text *>(val)){
					return new Assignment(op, var, val);
				}else{

					for(int j=0;j<rhs.size();j++){
						std::cout << rhs.at(j) << " ";
					}

					std::cout << "in assignment ";

					for(int j=0;j<in.size();j++){
						std::cout << in.at(j) << " ";
					}

					std::cout << "doesn't have a text value." << std::endl;

					throw std::exception();
				}
			}

		//if operator is any other assignment op
		}else{
			//only Num types can be assigned to Num types using arithmetic assignment ops
			if(Num *l = dynamic_cast<Num *>(var)){
				if(Num *r = dynamic_cast<Num *>(val)){
					return new Assignment(op, var, val);
				}else{

					for(int j=0;j<rhs.size();j++){
						std::cout << rhs.at(j) << " ";
					}

					std::cout << "in assignment ";

					for(int j=0;j<in.size();j++){
						std::cout << in.at(j) << " ";
					}

					std::cout << "doesn't have a numeric value." << std::endl;

					throw std::exception();
				}
			}
		}

		std::cout << "Something went wrong in parseStatement()" << std::endl;
		throw std::exception();
	}


	//parse a print statement and return a Print pointer
	if(in.size()){
		if(in.at(0) == "print"){
			in.erase(in.begin());
			return new Print(parseValue(in));
		}else if(NoneCall *call = parseNoneCall(in)){
			return call;
		}else if(in.at(0) == "end" && in.size() == 1){
			return new Return(NULL);
		}else if(Value *val = parseValue(in)){
			return new Return(val);
		}
	}


	return parseDeclarationStatement(in);
}
