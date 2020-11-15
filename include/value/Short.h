#ifndef SHORT_H
#define SHORT_H

#include <string>
#include "value/Num.h"

class Short : public Num{
public:
	Short();
	Short(short v);
	Short(std::string s);

	bool isLiteral();
	short getValue();

private:
	bool literal;
	short value;

};
#endif
