#include "statement/For.h"


For::For(Num *n, std::vector<line_t> b){
	num = n;
	body = b;
	val = NULL;
}

Num *For::getNum(){
	return num;
}

void For::setNum(Num *n){
	num = n;
}


std::vector<line_t> For::getBody(){
	return body;
}

void For::setBody(std::vector<line_t> b){
	body = b;
}

void For::addLine(line_t l){
	body.push_back(l);
}


Value *For::getVar(){
	return val;
}

void For::setVar(Value *v){
	val = v;
}
