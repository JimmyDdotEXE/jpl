#ifndef COMPARISON_H
#define COMPARISON_H

#include "value/Cond.h"

typedef enum{LESS, GREAT, LESSEQ, GREATEQ, EQUAL, NOTEQUAL} comp;


class Comparison: public Cond{
 public:
	Comparison(comp c, Value *l, Value *r);

	comp getOp();
  void setOp(comp c);

	Value *getLeft();
  void setLeft(Value *n);

	Value *getRight();
  void setRight(Value *n);

 private:
	comp op;
	Value *lhs;
	Value *rhs;
};
#endif
