#ifndef WHILE_H
#define WHILE_H

#include <vector>
#include "File.h"
#include "value/Cond.h"


class While: public Statement{
public:
	While(Cond *c, std::vector<line_t> b);

	Cond *getCond();
	void setCond(Cond *c);

	std::vector<line_t> getBody();
	void setBody(std::vector<line_t> b);
	void addLine(line_t l);

private:
	Cond *cond;
	std::vector<line_t> body;
};
#endif
