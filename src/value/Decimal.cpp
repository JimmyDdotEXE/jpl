#include "value/Decimal.h"


Decimal::Decimal(){
	literal = false;
	value = 0;
}

Decimal::Decimal(double v){
	literal = true;
	value = v;
}

Decimal::Decimal(std::string s, mutator m) : Num("double", s, m){
	literal = false;
	value = 0;
}

Decimal::Decimal(std::string n, std::vector<Value *> p) : Num("double", n, p){
	literal = false;
	value = 0;
}


bool Decimal::isLiteral(){
	return literal;
}

double Decimal::getValue(){
	return value;
}
