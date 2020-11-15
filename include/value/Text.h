#ifndef TEXT_H
#define TEXT_H

#include <string>
#include "value/Value.h"

class Text : public Value{
public:
	virtual ~Text();
	Text();
	Text(std::string t, std::string n);

};
#endif
