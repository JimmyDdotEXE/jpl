#include "statement/Print.h"
#include "statement/Assignment.h"
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

	//if parameter is an Assignment
	}else if(Assignment *s = dynamic_cast<Assignment *>(in)){
		return constructAssignment(s);
	}

	return "";
}
