#include <iostream>
#include "value/Concatenation.h"
#include "constructor/Constructor.h"
#include "constructor/ConstructText.h"


/*
	constructConcatenation function
	takes an Concatenation pointer as parameter
	builds a C++ std::string concatenation based on parameter
	returns a std::string
*/
std::string constructConcatenation(Concatenation *in){
	std::string ret = "";

	if(String *l = dynamic_cast<String *>(in->getLeft())){
		if(l->isLiteral()){
			ret += "std::string(" + constructString(l) + ")";
		}else{
			ret += constructString(l);
		}
	}else if(Char *l = dynamic_cast<Char *>(in->getLeft())){
		ret += "std::string(1, " + constructChar(l) + ")";
	}

	ret += " + ";

	if(String *r = dynamic_cast<String *>(in->getRight())){
		if(r->isLiteral()){
			ret += "std::string(" + constructString(r) + ")";
		}else{
			ret += constructString(r);
		}
	}else if(Char *r = dynamic_cast<Char *>(in->getRight())){
		ret += "std::string(1, " + constructChar(r) + ")";
	}

	return ret;
}


/*
	constructString function
	takes an String pointer as parameter
	builds a C++ std::string value based on parameter
	returns a std::string
*/
std::string constructString(String *in){

	if(Concatenation *t = dynamic_cast<Concatenation *>(in)){
		return constructConcatenation(t);
	}else{
		if(in->isVar()){
			if(checkScope(in)){
				return in->getName();
			}else{
				addToScope(in);
				return in->getType() + " " + in->getName();
			}
		}else{
			return "\"" + in->getValue() + "\"";
		}
	}
}


/*
	constructChar function
	takes an Char pointer as parameter
	builds a C++ char value based on parameter
	returns a std::string
*/
std::string constructChar(Char *in){
	if(in->isVar()){
		if(checkScope(in)){
			return in->getName();
		}else{
			addToScope(in);
			return in->getType() + " " + in->getName();
		}
	}else{
		std::string ret = "";

		ret.append(1, '\'');

		if(in->getEscape()){
			ret.append(1, '\\');
		}

		ret.append(1, in->getValue());
		ret.append(1, '\'');

		return ret;
	}
}


/*
	constructText function
	takes an Text pointer as parameter
	builds a C++ text value based on parameter
	returns a std::string
*/
std::string constructText(Text *in){

	if(Char *t = dynamic_cast<Char *>(in)){
		return constructChar(t);
	}else if(String *t = dynamic_cast<String *>(in)){
		return constructString(t);
	}

	return "";
}
