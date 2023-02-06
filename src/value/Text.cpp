#include "value/Text.h"


Text::~Text(){}

Text::Text(){}

Text::Text(std::string t, std::string n, mutator m) : Value(t, n, m){}

Text::Text(std::string t, std::string n, std::vector<Value *> p) : Value(t, n, p){}
