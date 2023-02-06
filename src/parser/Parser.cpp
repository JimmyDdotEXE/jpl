#include <iostream>
#include <algorithm>
#include <sstream>
#include "Util.h"
#include "value/Int.h"
#include "value/Bool.h"
#include "statement/If.h"
#include "statement/While.h"
#include "statement/For.h"
#include "statement/Function.h"
#include "statement/Return.h"
#include "parser/ParseNum.h"
#include "parser/ParseCond.h"
#include "parser/ParseText.h"
#include "parser/ParseStatement.h"
#include "parser/ParseFunction.h"
#include "parser/Parser.h"


//collection of know global variables
std::vector<Value *> globals;

//collection of know variables in the current scope
std::vector<Value *> vars;

//collection of know functions in the current scope
std::vector<Function *> functions;

//count of how many for-loops deep the parser is running
int loops = 0;


bool nameCheck(std::string s){
	for(int i=0;i<128;i++){
		if(s.find(i) != std::string::npos){
			std::cout << "invalid variable name \'" << s << "\'." << std::endl;
			throw std::exception();
		}

		if(i == 47){
			i = 57;
		}else if(i == 64){
			i = 90;
		}else if(i == 94){
			i = 95;
		}else if(i == 96){
			i = 122;
		}
	}

	if(numeric(s.substr(0, 1))){
		std::cout << "invalid variable name \'" << s << "\'." << std::endl;
		throw std::exception();
	}else if(std::find(reservedNames.begin(), reservedNames.end(), s) != reservedNames.end()){
		std::vector<std::string>::iterator it = std::find(reservedNames.begin(), reservedNames.end(), s);

		std::cout << "Name \'" << *it << "\' is reserved." << std::endl;
		throw std::exception();
	}else if(s == "loop"){
		std::cout << "Name \'" << s << "\' is reserved." << std::endl;
		throw std::exception();
	}else if(size_t pos = s.find("loop") == 0){
		if(numeric(s.substr(pos+4))){
			std::cout << "Name \'" << s << "\' is reserved." << std::endl;
			throw std::exception();
		}
	}

	return true;
}


bool returnTypeCheck(Return *ret, Function *fun){
	std::string type = fun->getType();

	bool none = false;
	bool cond = false;
	bool num = false;
	bool chr = false;
	bool str = false;

	if(type == "void"){
		none = true;
	}else if(type == "bool"){
		cond = true;
	}else if(type == "signed char" || type == "short" || type == "int" || type == "long" || type == "double"){
		num = true;
	}else if(type == "char"){
		chr = true;
	}else if(type == "std::string"){
		str = true;
	}

	Value *val = ret->getValue();
	if(val == NULL){
		if(none){
			return true;
		}else{
			return false;
		}
	}else if(dynamic_cast<Num *>(val) && num){
		return true;
	}else if(dynamic_cast<Cond *>(val) && cond){
		return true;
	}else if(dynamic_cast<Char *>(val) && chr){
		return true;
	}else if(dynamic_cast<String *>(val) && str){
		return true;
	}

	return false;
}


bool typeCheck(Value *v1, Value *v2){
	if(dynamic_cast<Num *>(v1) && dynamic_cast<Num *>(v2)){
		return true;
	}else if(dynamic_cast<Cond *>(v1) && dynamic_cast<Cond *>(v2)){
		return true;
	}else if(dynamic_cast<Char *>(v1) && dynamic_cast<Char *>(v2)){
		return true;
	}else if(dynamic_cast<String *>(v1) && dynamic_cast<String *>(v2)){
		return true;
	}

	return false;
}


/*
	lookupType function
	takes a string as parameter
	checks if string is in list of known types
	returns a bool
*/
bool lookupType(std::string type){
	if(std::find(types.begin(), types.end(), type) != types.end()){
		return true;
	}

	return false;
}


bool setScope(std::vector<Value *> in){
	vars = in;
	return true;
}

bool clearScope(){
	vars.clear();
	return true;
}


/*
	addVar function
	takes a Value pointer as parameter
	adds variable to current scope
	returns a bool
*/
bool addVar(Value *var){
	if(var->getMutator() & mut_GLOBAL){
		globals.push_back(var);
	}else{
		vars.push_back(var);
	}

	return true;
}

/*
	lookupVar function
	takes a string as parameter
	searchs vars vector for a variable with name that matches parameter
	returns a Var pointer
*/
Value *lookupVar(std::string var){
	//if input is "loop", search scope back to front for most recent 'loop' variable
	if(var == "loop"){
		for(int i=vars.size()-1;i >= 0;i--){
			if(size_t pos = vars.at(i)->getName().find("loop") != std::string::npos){
				if(numeric(vars.at(i)->getName().substr(pos+4))){
					return vars.at(i);
				}
			}
		}
	}

	//search scope front to back for a variable with matching name
	for(int i=0;i < vars.size();i++){
		if(vars.at(i)->getName() == var){
			return vars.at(i);
		}
	}

	//search global variables front to back for a variable with matching name
	for(int i=0;i < globals.size();i++){
		if(globals.at(i)->getName() == var){
			if(!(globals.at(i)->getMutator() & mut_STATIC) || globals.at(i)->getFile() == currentFile){
				return globals.at(i);
			}
		}
	}

	return NULL;
}


/*
	lookupFunction function
	takes a string as parameter
	searchs funcs vector for a function with a name that matches the parameter
	returns a Function pointer
*/
Function *lookupFunction(std::string n){
	//search scope front to back for a function with a matching name
	for(int i=0;i < functions.size();i++){
		if(functions.at(i)->getName() == n){
			return functions.at(i);
		}
	}

	return NULL;
}


/*
	CountExtraLines function
	Takes a vector of line structures as parameter
	recursively counts the number of lines in the parameter and contained collections line structures
	returns a count of lines as an int
*/
int countExtraLines(std::vector<line_t> lines){
	int ret = lines.size();

	//loop through all lines of parameter to count any extra lines
	for(int i=0;i<lines.size();i++){
		//if line contains an If statement, recursively count extra lines
		if(If *stmt = dynamic_cast<If *>(lines.at(i).stmt)){
			ret += countExtraLines(stmt->getBody());

		//if line contains an While statement, recursively count extra lines
		}else if(While *stmt = dynamic_cast<While *>(lines.at(i).stmt)){
			ret += countExtraLines(stmt->getBody());

		//if line contains an For statement, recursively count extra lines
		}else if(For *stmt = dynamic_cast<For *>(lines.at(i).stmt)){
			ret += countExtraLines(stmt->getBody());
		}
	}

	return ret;
}




std::vector<line_t> parseLines(std::vector<std::string> input, int depth){
	//make a backup of the scope of variables right at the start of the parser
	std::vector<Value *> oldScope(vars.size());
	std::copy(vars.begin(), vars.end(), oldScope.begin());

	std::vector<line_t> ret;

	int lastLiveLine = 0;

	//read next line from file
	for(int j=0;j < input.size();j++){
		std::vector<std::string> holder;
		std::string line = input.at(j);
		line_t ln;
		ln.stmt = NULL;
		std::string comment = "";

		//look for a comment in the current line
		size_t cPos = line.find('#');
		if(cPos != std::string::npos){
			comment = line.substr(cPos+1);
			line = line.substr(0, cPos);
		}

		bool liveLine = false;
		bool eol = true;
		int numTabs = 0;

		//count the tab depth of the line
		for(int i=0;line[i] == '\t';i++){
			numTabs++;
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

		//if the measured tab depth doesn't match the given depth parameter
		//and the line does have a statement to parse
		//swap in the old variable scope and return
		if(numTabs != depth && ss.size()){
			vars.swap(oldScope);

			for(int i=lastLiveLine;i<j-1 && ret.size();i++){
				ret.pop_back();
			}

			return ret;
		}


		//for each line in ss
		for(int i=0;i<ss.size();i++){
			//look for the terminal character ':'
			size_t term = ss.at(i).find(':');

			//if no terminal character is found, continue
			if(term == std::string::npos){
				continue;
			}

			std::vector<std::string> lhs;

			//add all strings on the left of the terminal character to lhs vector
			for(int x=0;x<ss.size();x++){
				if(x<i){
					lhs.push_back(ss.at(x));
				}
			}

			//add all characters left of terminal character to lhs vector as a string
			if(ss.at(i).substr(0, term) != ""){
				lhs.push_back(ss.at(i).substr(0, term));
			}

			//add all lines past the current one to a std::vector<std::string> to be parsed as the body of a statement
			std::vector<std::string> body;
			for(int x=j+1;x < input.size();x++){
				body.push_back(input.at(x));
			}

			//parse an if statement
			if(lhs.at(0) == "if"){
				lhs.erase(lhs.begin());

				If *tmp = new If(parseCond(lhs), parseLines(body, depth+1));
				j += countExtraLines(tmp->getBody());
				ln.stmt = tmp;

			//parse an elseif statement
			}else if(lhs.at(0) == "elseif"){
				if(If *stmt = dynamic_cast<If *>(ret.back().stmt)){
					lhs.erase(lhs.begin());

					If *tmp = new If(parseCond(lhs), parseLines(body, depth+1));
					j += countExtraLines(tmp->getBody());
					ln.stmt = tmp;
					stmt->setElse(tmp);
				}

			//parse an else statement
			}else if(lhs.at(0) == "else"){
				if(If *stmt = dynamic_cast<If *>(ret.back().stmt)){
					lhs.erase(lhs.begin());

					If *tmp = new If(new Bool(true), parseLines(body, depth+1));
					j += countExtraLines(tmp->getBody());
					ln.stmt = tmp;
					stmt->setElse(tmp);
				}

			//parse a while-loop
			}else if(lhs.at(0) == "while"){
				lhs.erase(lhs.begin());

				While *tmp = new While(parseCond(lhs), parseLines(body, depth+1));
				j += countExtraLines(tmp->getBody());
				ln.stmt = tmp;

			//parse a for-loop
			}else if(lhs.at(0) == "for"){
				lhs.erase(lhs.begin());

				loops++;
				vars.push_back(new Int("loop" + numString(loops)));

				For *tmp = new For(parseNum(lhs), parseLines(body, depth+1));
				tmp->setVar(vars.back());
				j += countExtraLines(tmp->getBody());
				ln.stmt = tmp;

				vars.pop_back();
				loops--;
			}
		}

		//if no statement has been found make a call to parseStatement()
		if(!ln.stmt){
			ln.stmt = parseStatement(ss);
		}

		liveLine = ln.stmt;

		ln.comment = comment;
		ln.tabDepth = numTabs;
		ln.live = liveLine;
		ret.push_back(ln);

		if(liveLine){
			lastLiveLine = j;
		}
	}

	return ret;
}

bool parser(std::vector<File *> files){
	for(int i=0;i<files.size();i++){
		std::vector<Function *> funcs = files.at(i)->getFunctions();

		for(int j=0;j<funcs.size();j++){
			funcs.at(j)->file = files.at(i);
			functions.push_back(funcs.at(j));
		}
	}


	for(int i=0;i<files.size();i++){
		currentFile = files.at(i);
		std::vector<Function *> funcs = currentFile->getFunctions();

		for(int j=0;j<funcs.size();j++){

			setScope(funcs.at(j)->getParameters());
			funcs.at(j)->setBody(parseLines(funcs.at(j)->getTemp(), 1));
			clearScope();
		}

		for(int j=0;j<funcs.size();j++){
			std::vector<line_t> lines = funcs.at(j)->getBody();
			bool guaranteedReturn = false;

			for(int k=0;k<lines.size();k++){
				if(Return *stmt = dynamic_cast<Return *>(lines.at(k).stmt)){
					if(!returnTypeCheck(stmt, funcs.at(j))){
						std::cout << "Function " << funcs.at(j)->getName() << " missmatched return type.\n";
					}else if(lines.at(k).tabDepth == 1){
						guaranteedReturn = true;
					}
				}else if(While *stmt = dynamic_cast<While *>(lines.at(k).stmt)){
					std::vector<line_t> body = stmt->getBody();
					lines.insert(lines.end(), body.begin(), body.end());
				}else if(For *stmt = dynamic_cast<For *>(lines.at(k).stmt)){
					std::vector<line_t> body = stmt->getBody();
					lines.insert(lines.end(), body.begin(), body.end());
				}else if(If *stmt = dynamic_cast<If *>(lines.at(k).stmt)){
					std::vector<line_t> body = stmt->getBody();
					lines.insert(lines.end(), body.begin(), body.end());

					while(stmt->getElse()){
						stmt = stmt->getElse();

						body = stmt->getBody();
						lines.insert(lines.end(), body.begin(), body.end());
					}
				}
			}

			if(!guaranteedReturn && funcs.at(j)->getType() != "none"){
				std::cout << "Function " << funcs.at(j)->getName() << " lacks guaranteed return.\n";
			}
		}

		if(i == 0){
			currentFile->setLines(parseLines(currentFile->getHolder()));
		}
	}

	return true;
}
