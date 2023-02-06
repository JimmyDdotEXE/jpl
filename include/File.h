#ifndef FILE_H
#define FILE_H

#include <string>
#include <vector>
#include "statement/Assignment.h"
#include "value/Value.h"


typedef struct{
	Statement *stmt;
	std::string comment;
	int tabDepth;
	bool live;
} line_t;

typedef struct{
	Assignment *assignment;
	std::string sideComment;
	std::vector<std::string> topComment;
} global_t;


class Function;


class File{
public:
	File(std::string s);

	std::string getName();
	std::string getPath();
	std::vector<Function *> getFunctions();
	std::vector<global_t> getGlobals();
	std::vector<File *> getInclusions();
	std::vector<std::string> getHolder();
	std::vector<line_t> getLines();

	bool setName(std::string s);
	bool setPath(std::string s);
	bool setFunctions(std::vector<Function *> f);
	bool setGlobals(std::vector<global_t> g);
	bool setHolder(std::vector<std::string> s);
	bool setLines(std::vector<line_t> l);

	bool addInclusion(File *f);

private:
	std::string name;
	std::string path;
	std::vector<Function *> functions;
	std::vector<global_t> globals;
	std::vector<File *> includes;

	std::vector<std::string> holder;
	std::vector<line_t> lines;
};
#endif
