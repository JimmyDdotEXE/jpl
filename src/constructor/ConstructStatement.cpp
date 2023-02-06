#include "statement/NoneCall.h"
#include "statement/Print.h"
#include "statement/Return.h"
#include "statement/Assignment.h"
#include "File.h"
#include "constructor/ConstructValue.h"
#include "constructor/ConstructCond.h"
#include "constructor/ConstructStatement.h"


/*
	constructAssignment function
	takes an Assignment pointer as parameter
	builds a C++ assignment based on parameter
	returns a std::string
*/
std::string constructAssignment(Assignment *in){

	std::string ret = constructValue(in->getLeft());

	switch(in->getOp()){
		case ASSIGN:
			ret += " = ";
			break;
		case ADDASSIGN:
			ret += " += ";
			break;
		case SUBASSIGN:
			ret += " -= ";
			break;
		case MULTASSIGN:
			ret += " *= ";
			break;
		case DIVASSIGN:
			ret += " /= ";
			break;
	}

	ret += constructValue(in->getRight());

	return ret + ";";
}


/*
	constructStatement function
	takes a Statement pointer as parameter
	builds a C++ statement based on parameter
	returns a std::string
*/
std::string constructStatement(Statement *in){

	//if parameter is a Print
	if(Print *s = dynamic_cast<Print *>(in)){
		if(Cond *c = dynamic_cast<Cond *>(s->getValue())){
			return "std::cout << (" + constructCond(c) + " ? \"True\" : \"False\")" + " << std::endl;";
		}else{
			return "std::cout << " + constructValue(s->getValue()) + " << std::endl;";
		}

	}else if(Return *s = dynamic_cast<Return *>(in)){
		if(s->getValue()){
			return "return " + constructValue(s->getValue()) + ";";
		}else{
			return "return;";
		}

	//if parameter is an Assignment
	}else if(Assignment *s = dynamic_cast<Assignment *>(in)){
		return constructAssignment(s);

	}else if(NoneCall *s = dynamic_cast<NoneCall *>(in)){
		std::string ret = s->getName() + "(";

		for(int i=0;i<s->getParameters().size();i++){
			ret += constructValue(s->getParameters().at(i));
						
			if(i != s->getParameters().size()-1){
				ret += ", ";
			}
		}

		return ret + ");";
	}

	return "";
}




std::vector<std::string> constructGlobalDeclarations(std::vector<global_t> g){
	std::vector<std::string> ret;

	for(int i=0;i < g.size();i++){
		std::string temp = "extern ";
		Value *var = g.at(i).assignment->getLeft();

		if(var->getMutator() & mut_STATIC){
			continue;
		}

		if(var->getMutator() & mut_CONST){
			temp += "const ";
		}

		temp += var->getType() + " " + var->getName() + ";";

		ret.push_back(temp);
	}

	return ret;
}

std::vector<std::string> constructGlobalDefinitions(std::vector<global_t> g){
	std::vector<std::string> ret;

	for(int i=0;i < g.size();i++){
		for(int j=0;j<g.at(i).topComment.size();j++){
			ret.push_back("//" + g.at(i).topComment.at(j));
		}

		if(g.at(i).sideComment != ""){
			ret.push_back(constructAssignment(g.at(i).assignment) + "\t//" + g.at(i).sideComment);
		}else{
			ret.push_back(constructAssignment(g.at(i).assignment));
		}
	}

	return ret;
}
