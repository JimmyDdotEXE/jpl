#include "value/Comparison.h"


Comparison::Comparison(comp c, Value *l, Value *r){
  op = c;

  lhs = l;
  rhs = r;
}


comp Comparison::getOp(){
  return op;
}

void Comparison::setOp(comp c){
  op = c;
}


Value *Comparison::getLeft(){
  return lhs;
}

void Comparison::setLeft(Value *v){
  lhs = v;
}


Value *Comparison::getRight(){
  return rhs;
}

void Comparison::setRight(Value *v){
  rhs = v;
}
