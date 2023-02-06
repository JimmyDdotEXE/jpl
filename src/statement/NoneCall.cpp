#include "statement/NoneCall.h"


NoneCall::NoneCall(std::string n){
	name = n;
}

NoneCall::NoneCall(std::string n, std::vector<Value *> p){
	name = n;
	parameters = p;
}


std::string NoneCall::getName(){
	return name;
}

std::vector<Value *> NoneCall::getParameters(){
	return parameters;
}
