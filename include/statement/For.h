#ifndef FOR_H
#define FOR_H

#include <vector>
#include "File.h"
#include "value/Num.h"


class For: public Statement{
public:
  For(Num *n, std::vector<line_t> b);

	Num *getNum();
	void setNum(Num *n);

	std::vector<line_t> getBody();
	void setBody(std::vector<line_t> b);
	void addLine(line_t l);

	Value *getVar();
	void setVar(Value *v);

private:
	Num *num;
	std::vector<line_t> body;

	Value *val;
};
#endif
