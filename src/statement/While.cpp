#include "statement/While.h"


While::While(Cond *c, std::vector<line_t> b){
	cond = c;
	body = b;
}


Cond *While::getCond(){
	return cond;
}

void While::setCond(Cond *c){
	cond = c;
}


std::vector<line_t> While::getBody(){
	return body;
}

void While::setBody(std::vector<line_t> b){
	body = b;
}

void While::addLine(line_t l){
	body.push_back(l);
}
