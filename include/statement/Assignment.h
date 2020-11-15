#ifndef ASSIGNMENT_H
#define ASSIGNMENT_H

#include "statement/Statement.h"
#include "value/Value.h"

typedef enum{ASSIGN, ADDASSIGN, SUBASSIGN, MULTASSIGN, DIVASSIGN} assign;


class Assignment: public Statement{
public:
	Assignment(assign o, Value *v, Value *n);

	assign getOp();
	Value *getLeft();
	Value *getRight();

private:
	assign op;
	Value *lhs;
	Value *rhs;
};
#endif
