#ifndef IF_H
#define IF_H

#include <vector>
#include "parser/Parser.h"
#include "value/Cond.h"


class If: public Statement{
public:
  If(Cond *c, std::vector<line_t> t);
  If(Cond *c, std::vector<line_t> t, If *e);

  Cond *getCond();
  void setCond(Cond *c);

  std::vector<line_t> getBody();
  void setBody(std::vector<line_t> t);
  void addLine(line_t t);

  If *getElse();
  void setElse(If *e);

private:
	Cond *cond;
	std::vector<line_t> then;
	If *els;

};
#endif
