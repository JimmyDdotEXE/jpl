#ifndef PRINT_H
#define PRINT_H

#include "value/Value.h"
#include "statement/Statement.h"

class Print: public Statement{
public:
	Print(Value *v);

	Value *getValue();

private:
	Value *value;
};
#endif
