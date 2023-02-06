#ifndef RETURN_H
#define RETURN_H

#include "value/Value.h"
#include "statement/Statement.h"

class Return: public Statement{
public:
	Return(Value *v);

	Value *getValue();

private:
	Value *value;
};
#endif
