#include "value/Logic.h"


Logic::Logic(log lo, Cond *l, Cond *r){
  op = lo;

  lhs = l;
  rhs = r;
}


log Logic::getOp(){
  return op;
}

void Logic::setOp(log lo){
  op = lo;
}


Cond *Logic::getLeft(){
  return lhs;
}

void Logic::setLeft(Cond *c){
  lhs = c;
}


Cond *Logic::getRight(){
  return rhs;
}

void Logic::setRight(Cond *c){
  rhs = c;
}
