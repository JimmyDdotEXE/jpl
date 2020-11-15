#include "value/Bool.h"
#include "value/Comparison.h"
#include "value/Logic.h"
#include "value/Group.h"
#include "value/Negation.h"
#include "constructor/Constructor.h"
#include "constructor/ConstructValue.h"
#include "constructor/ConstructNum.h"
#include "constructor/ConstructCond.h"
#include <iostream>

/*
	constructLogic function
	takes an Logic pointer as parameter
	builds a C++ logical operation based on parameter
	returns a std::string
*/
std::string constructLogic(Logic *in){
	std::string ret;

	Cond *lhs = in->getLeft();
	log op = in->getOp();
	Cond *rhs = in->getRight();

	ret = constructCond(lhs);

	switch(op){
		case AND:
			ret += " && ";
			break;
		case OR:
			ret += " || ";
			break;
	}

	ret += constructCond(rhs);

	return ret;
}


/*
	constructComparison function
	takes an Comparison pointer as parameter
	builds a C++ comparison based on parameter
	returns a std::string
*/
std::string constructComparison(Comparison *in){
	std::string ret;

	Value *lhs = in->getLeft();
	comp op = in->getOp();
	Value *rhs = in->getRight();

	ret = constructValue(lhs);

	switch(op){
		case LESS:
			ret += " < ";
			break;
		case GREAT:
			ret += " > ";
			break;
		case LESSEQ:
			ret += " <= ";
			break;
		case GREATEQ:
			ret += " >= ";
			break;
		case EQUAL:
			ret += " == ";
			break;
		case NOTEQUAL:
			ret += " != ";
			break;
	}

	ret += constructValue(rhs);

	return ret;
}


/*
	constructCond function
	takes an Cond pointer as parameter
	builds a C++ conditional value based on parameter
	returns a std::string
*/
std::string constructCond(Cond *in){

	if(Logic *c = dynamic_cast<Logic *>(in)){
		return constructLogic(c);
	}else if(Comparison *c = dynamic_cast<Comparison *>(in)){
		return constructComparison(c);
	}else if(Group *c = dynamic_cast<Group *>(in)){
		return "(" + constructCond(c->getCond()) + ")";
	}else if(Negation *c = dynamic_cast<Negation *>(in)){
		return "!" + constructCond(c->getCond());
	}else if(Bool *c = dynamic_cast<Bool *>(in)){
		if(c->isVar()){
			if(checkScope(c)){
				return c->getName();
			}else{
				addToScope(c);
				return c->getType() + " " + c->getName();
			}
		}else if(c->getValue()){
			return "true";
		}else{
			return "false";
		}
	}

	return "";
}
