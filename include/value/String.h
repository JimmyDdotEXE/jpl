#ifndef STRING_H
#define STRING_H

#include <string>
#include "value/Text.h"

class String : public Text{
public:
	String();
	String(const char *s);
	String(std::string s);

	bool isLiteral();
	std::string getValue();

private:
	bool literal;
	std::string value;

};
#endif
