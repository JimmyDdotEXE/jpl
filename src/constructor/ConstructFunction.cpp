#include "constructor/Constructor.h"
#include "constructor/ConstructValue.h"
#include "constructor/ConstructFunction.h"


std::string constructFunctionCall(Value *in){
	std::string ret = in->getName() + "(";

	std::vector<Value *> params = in->getParameters();
	for(int i=0;i<params.size();i++){
		ret += constructValue(params.at(i));

		if(i < params.size()-1){
			ret += ", ";
		}
	}

	return ret + ")";
}


std::string constructFunctionHeader(Function *in){
	std::string ret = in->getType() + " " + in->getName() + "(";

	std::vector<Value *> params = in->getParameters();
	for(int i=0;i<params.size();i++){
		ret += constructValue(params.at(i));

		if(i < params.size()-1){
			ret += ", ";
		}
	}

	clearConstructorScope();

	return ret + ");";
}

std::vector<std::string> constructFunctionHeaders(std::vector<Function *> in){
	std::vector<std::string> ret;

	for(int i=0;i<in.size();i++){
		ret.push_back(constructFunctionHeader(in.at(i)));
	}

	return ret;
}


std::vector<std::string> constructFunction(Function *in){
	std::vector<std::string> ret;

	for(int i=0;i<in->getTopComment().size();i++){
		ret.push_back("//" + in->getTopComment().at(i));
	}

	ret.push_back(in->getType() + " " + in->getName() + "(");

	std::vector<Value *> params = in->getParameters();
	for(int i=0;i<params.size();i++){
		ret.back() += constructValue(params.at(i));

		if(i < params.size()-1){
			ret.back() += ", ";
		}
	}

	ret.back() += "){";

	if(in->getSideComment() != ""){
		ret.back() += "\t//" + in->getSideComment();
	}

	std::vector<std::string> body = constructor(in->getBody());
	ret.insert(ret.end(), body.begin(), body.end());

	ret.push_back("}");

	clearConstructorScope();

	return ret;
}

std::vector<std::string> constructFunctions(std::vector<Function *> in){
	std::vector<std::string> ret;

	for(int i=0;i<in.size();i++){
		std::vector<std::string> func = constructFunction(in.at(i));
		ret.insert(ret.end(), func.begin(), func.end());

		if(i < in.size()-1){
			ret.push_back("\n\n");
		}
	}

	return ret;
}
