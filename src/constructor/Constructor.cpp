#include <iostream>
#include <sstream>
#include <algorithm>
#include "value/Num.h"
#include "value/Equation.h"
#include "value/Logic.h"
#include "value/Comparison.h"
#include "statement/If.h"
#include "statement/While.h"
#include "statement/For.h"
#include "statement/Assignment.h"
#include "statement/Print.h"
#include "constructor/ConstructNum.h"
#include "constructor/ConstructCond.h"
#include "constructor/ConstructStatement.h"
#include "constructor/Constructor.h"


//collection of variables in the current scope
std::vector<Value *> variables;


/*
	addToScope function
	takes a Value pointer as parameter
	adds parameter to current scope if it's not already in the scope
	returns a bool
*/
bool addToScope(Value *var){
	if(!checkScope(var)){
		variables.push_back(var);

		return true;
	}

	return false;
}


/*
	checkScope function
	takes a Value pointer as parameter
	searches current scope for parameter
	returns a bool
*/
bool checkScope(Value *var){
	if(std::find(variables.begin(), variables.end(), var) != variables.end()){
		return true;
	}

	return false;
}




/*
	constructor function
	takes a std::vector<line_t> as parameter
	constructs lines of C++ code based on parameter
	returns a std::vector<std::string>
*/
std::vector<std::string> constructor(std::vector<line_t> input){
	//make a backup of the scope of variables right at the start of the constructor
	std::vector<Value *> oldScope(variables.size());
	std::copy(variables.begin(), variables.end(), oldScope.begin());

	//declare a std::vector<std::string> to hold the return value
	std::vector<std::string> ret;

	//the number of extra tabs that will need to be added to each line
	//this is needed because a main function isn't needed in JPL, but is required by C++
	int extraTabs = 0;

	//if the tab depth of the first line of input is 0
	if(input.at(0).tabDepth == 0){
		//include needed headers and wrap the code in a main function
		ret.push_back("#include <iostream>\n#include <string>\n\n");
		ret.push_back("int main(int argc, char *argv[]){");

		//extraTabs needs to be 1 now so all the lines wrapped in main() are indented
		extraTabs = 1;
	}


	//for each line in the input
	for(int i=0;i<input.size();i++){
		std::vector<std::string> body;
		std::string ln = "";

		//get the statement of the current line
		Statement *line = input.at(i).stmt;

		if(input.at(i).stmt || input.at(i).comment != ""){
			//add tabDepth+extraTabs number of tabs to the start of the line
			for(int x=0;x<input.at(i).tabDepth + extraTabs;x++){
				ln += "\t";
			}
		}


		//if the statement of the current line is an If statement
		if(If *stmt = dynamic_cast<If *>(line)){
			std::string tmp = "";

			//the constructor isn't focused on the first line of the input
			if(i > 0){
				//if the previous line contains an If statement
				if(If *prv = dynamic_cast<If *>(input.at(i-1).stmt)){
					//if that previous If statement has an else that is equal to the current If statement
					if(prv->getElse() == stmt){
						//if the current If statement lacks an else statement, and it's conditional is 'true'
						if(stmt->getElse() == NULL && constructCond(stmt->getCond()) == "true"){
							//the current If statement represents an else statement
							ret.erase(ret.end());
							tmp = "}else{";

						//the current If statement represents an else-if statement
						}else{
							ret.erase(ret.end());
							tmp = "}else if(" + constructCond(stmt->getCond()) + "){";
						}
					}
				}
			}

			//no temp value has been built yet, it must be a normal if statement
			if(tmp == "")
				tmp = "if(" + constructCond(stmt->getCond()) + "){";

			//add the temp value to the current line that's being built
			ln += tmp;

			//construct the statement's body
			body = constructor(stmt->getBody());

			//set the closing brace at the tab depth
			std::string tabs;
			for(int j=0;j<input.at(i).tabDepth;j++)
				tabs += '\t';

			body.push_back(tabs + "}");

		//if the statement of the current line is a While statement
		}else if(While *stmt = dynamic_cast<While *>(line)){
			//construct the start of the while-loop and the statement's conditional
			ln += "while(" + constructCond(stmt->getCond()) + "){";

			//construct the statement's body
			body = constructor(stmt->getBody());

			//set the closing brace at the tab depth
			std::string tabs;
			for(int j=0;j<input.at(i).tabDepth;j++)
				tabs += '\t';

			body.push_back(tabs + "}");

		//if the statement of the current line is a For statement
		}else if(For *stmt = dynamic_cast<For *>(line)){
			//backup variable scope before constructing the for-loop
			std::vector<Value *> preLoop(variables.size());
			std::copy(variables.begin(), variables.end(), preLoop.begin());

			//construct the start of the for-loop and the statement's iteration number
			std::string v = stmt->getVar()->getName();
			ln += "for(" + constructNum(dynamic_cast<Num *>(stmt->getVar())) + "=0;" + v + "<" + constructNum(stmt->getNum()) + ";" + v + "++){";

			//construct the statement's body
			body = constructor(stmt->getBody());

			//set the preLoop variable scope to be the current scope
			variables.swap(preLoop);

			//set the closing brace at the tab depth
			std::string tabs;
			for(int j=0;j<input.at(i).tabDepth;j++)
				tabs += '\t';

			body.push_back(tabs + "}");

		//if a statement has not been constructed yet for the line make a call to constructStatement()
		}else{
			ln += constructStatement(line);
		}


		//if the current line has a comment, add it to line as C++ comment
		if(input.at(i).comment != ""){
			//if the line contains a statement, put a tab between the statement and comment
			if(input.at(i).stmt)
				ln += '\t';

			ln += "//" + input.at(i).comment;
		}

		//add the line to the end of the return vector
		ret.push_back(ln);

		//for each line in the body vector
		for(int x=0;x<body.size();x++){
			std::string tabs;

			//make a string of tabs that is extraTabs long
			for(int j=0;j<extraTabs;j++)
				tabs += '\t';

			if(body.at(x) != ""){
				//add the extra tabs and the body line the return vector
				ret.push_back(tabs + body.at(x));
			}else{
				ret.push_back(body.at(x));
			}
		}
	}

	//add brace to close main() if tabDepth is 0
	if(input.at(0).tabDepth == 0){
		ret.push_back("}");
	}

	//swap in the old variable scope before returning from constructor
	variables.swap(oldScope);

	return ret;
}
