#include "value/Cond.h"


Cond::~Cond(){}

Cond::Cond(){}

Cond::Cond(std::string t, std::string n, mutator m) : Value(t, n, m){}

Cond::Cond(std::string t, std::string n, std::vector<Value *> p) : Value(t, n, p){}
