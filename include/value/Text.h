#ifndef TEXT_H
#define TEXT_H

#include <string>
#include <vector>
#include "value/Value.h"

class Text : public Value{
public:
	virtual ~Text();
	Text();
	Text(std::string t, std::string n, mutator m=mut_NONE);
	Text(std::string t, std::string n, std::vector<Value *> p);

};
#endif
