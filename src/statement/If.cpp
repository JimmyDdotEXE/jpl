#include "statement/If.h"


If::If(Cond *c, std::vector<line_t> t){
  cond = c;
  then = t;
	els = NULL;
}

If::If(Cond *c, std::vector<line_t> t, If *e){
  cond = c;
  then = t;
  els = e;
}


Cond *If::getCond(){
  return cond;
}

void If::setCond(Cond *c){
  cond = c;
}


std::vector<line_t> If::getBody(){
  return then;
}

void If::setBody(std::vector<line_t> t){
  then = t;
}

void If::addLine(line_t t){
  then.push_back(t);
}


If *If::getElse(){
  return els;
}

void If::setElse(If *e){
  els = e;
}
