#include "value/Num.h"


Num::~Num(){}

Num::Num(){}

Num::Num(std::string t, std::string n, mutator m) : Value(t, n, m){}

Num::Num(std::string t, std::string n, std::vector<Value *> p) : Value(t, n, p){}
