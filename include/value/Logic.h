#ifndef LOGIC_H
#define LOGIC_H

#include "value/Cond.h"

typedef enum{AND, OR} log;


class Logic: public Cond{
 public:
	Logic(log lo, Cond *l, Cond *r);

	log getOp();
  void setOp(log lo);

	Cond *getLeft();
  void setLeft(Cond *c);

	Cond *getRight();
  void setRight(Cond *c);

 private:
	log op;
	Cond *lhs;
	Cond *rhs;
};
#endif
