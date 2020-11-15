#include "value/Decimal.h"


Decimal::Decimal(){
	literal = false;
	value = 0;
}

Decimal::Decimal(double v){
	literal = true;
	value = v;
}

Decimal::Decimal(std::string s) : Num("double", s){
	literal = false;
	value = 0;
}


bool Decimal::isLiteral(){
	return literal;
}

double Decimal::getValue(){
	return value;
}
