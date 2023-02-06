#ifndef FUNCTION_H
#define FUNCTION_H

#include <string>
#include <vector>
#include "File.h"
#include "value/Value.h"


class Function: public Statement{
public:
	Function();
  Function(std::string t, std::string n, std::vector<Value *> p);

	std::string getType();
	std::string getName();
	std::vector<Value *> getParameters();
	std::vector<line_t> getBody();
	std::vector<std::string> getTemp();
	std::string getSideComment();
	std::vector<std::string> getTopComment();

	void setType(std::string t);
	void setName(std::string n);
	void setParameters(std::vector<Value *> p);
	void setBody(std::vector<line_t> b);
	void setTemp(std::vector<std::string> t);
	bool setSideComment(std::string comment);
	bool setTopComment(std::vector<std::string> comment);

	void addLine(line_t l);

	File *file;
private:
	std::string type;
	std::string name;
	std::vector<Value *> parameters;
	std::vector<line_t> body;

	std::string sideComment;
	std::vector<std::string> topComment;

	std::vector<std::string> temp;
};
#endif
