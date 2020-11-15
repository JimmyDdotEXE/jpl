#ifndef VALUE_H
#define VALUE_H

#include <string>

class Value{
public:
	virtual ~Value();
	Value();
	Value(std::string t, std::string n);

	bool isVar();

	std::string getType();
	std::string getName();

private:
	bool var;
	std::string type;
	std::string name;

};
#endif
