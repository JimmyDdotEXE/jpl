#ifndef STRING_H
#define STRING_H

#include <string>
#include <vector>
#include "value/Text.h"

class String : public Text{
public:
	String();
	String(const char *s);
	String(std::string s, mutator m=mut_NONE);
	String(std::string n, std::vector<Value *> p);

	bool isLiteral();
	std::string getValue();

private:
	bool literal;
	std::string value;

};
#endif
