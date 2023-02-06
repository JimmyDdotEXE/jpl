#ifndef NONECALL_H
#define NONECALL_H

#include <string>
#include <vector>
#include "value/Value.h"
#include "statement/Statement.h"

class NoneCall : public Statement{
public:
	NoneCall(std::string n);
	NoneCall(std::string n, std::vector<Value *> p);

	std::string getName();
	std::vector<Value *> getParameters();

private:
	std::string name;
	std::vector<Value *> parameters;

};
#endif
