#include <sstream>
#include "Util.h"
#include "value/Byte.h"
#include "value/Short.h"
#include "value/Int.h"
#include "value/Long.h"
#include "value/Decimal.h"
#include "value/Equation.h"
#include "value/Group.h"
#include "value/Negative.h"
#include "constructor/Constructor.h"
#include "constructor/ConstructNum.h"


/*
	constructEquation function
	takes an pointer reference as parameter
	builds a C++ equation based on parameter
	returns a std::string
*/
std::string constructEquation(Equation *in){
	std::string ret;

	Num *lhs = in->getLeft();
	oper op = in->getOp();
	Num *rhs = in->getRight();

	ret = constructNum(lhs);

	switch(op){
		case ADD:
			ret += " + ";
			break;
		case SUB:
			ret += " - ";
			break;
		case MULT:
			ret += " * ";
			break;
		case DIV:
			ret += " / ";
			break;
		case REM:
			ret += " % ";
			break;
	}

	ret += constructNum(rhs);

	return ret;
}


/*
	constructNum function
	takes an Num pointer as parameter
	builds a C++ numerical value based on parameter
	returns a std::string
*/
std::string constructNum(Num *in){

	if(Equation *n = dynamic_cast<Equation *>(in)){
		return constructEquation(n);
	}else if(Group *n = dynamic_cast<Group *>(in)){
		return "(" + constructNum(n->getNum()) + ")";
	}else if(Negative *n = dynamic_cast<Negative *>(in)){
		return "-" + constructNum(n->getNum());
	}else if(Byte *n = dynamic_cast<Byte *>(in)){
		if(n->isVar()){
			if(checkScope(n)){
				return n->getName();
			}else{
				addToScope(n);
				return n->getType() + " " + n->getName();
			}
		}else{
			return numString(n->getValue());
		}
	}else if(Short *n = dynamic_cast<Short *>(in)){
		if(n->isVar()){
			if(checkScope(n)){
				return n->getName();
			}else{
				addToScope(n);
				return n->getType() + " " + n->getName();
			}
		}else{
			return numString(n->getValue());
		}
	}else if(Int *n = dynamic_cast<Int *>(in)){
		if(n->isVar()){
			if(checkScope(n)){
				return n->getName();
			}else{
				addToScope(n);
				return n->getType() + " " + n->getName();
			}
		}else{
			return numString(n->getValue());
		}
	}else if(Long *n = dynamic_cast<Long *>(in)){
		if(n->isVar()){
			if(checkScope(n)){
				return n->getName();
			}else{
				addToScope(n);
				return n->getType() + " " + n->getName();
			}
		}else{
			return numString(n->getValue());
		}
	}else if(Decimal *n = dynamic_cast<Decimal *>(in)){
		if(n->isVar()){
			if(checkScope(n)){
				return n->getName();
			}else{
				addToScope(n);
				return n->getType() + " " + n->getName();
			}
		}else{
			std::ostringstream stream;
			stream << n->getValue();

			return stream.str();
		}
	}

	return "";
}
