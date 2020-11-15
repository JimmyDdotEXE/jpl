#ifndef CHAR_H
#define CHAR_H

#include <string>
#include "value/Text.h"

class Char : public Text{
public:
	Char();
	Char(char c, bool esc=false);
	Char(std::string s);

	bool isLiteral();
	char getValue();
	bool getEscape();

private:
	bool literal;
	char value;
	bool escape;

};
#endif
