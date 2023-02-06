#ifndef VALUE_H
#define VALUE_H

#include <string>
#include <vector>

class File;

typedef enum{
	mut_NONE = 0x0,
	mut_GLOBAL = 0x2,
	mut_CONST = 0x4,
	mut_STATIC = 0x8
} mutator;

mutator operator |(mutator const& l, mutator const& r);


class Value{
public:
	virtual ~Value();
	Value();
	Value(std::string t, std::string n, mutator m=mut_NONE);
	Value(std::string t, std::string n, std::vector<Value *> p);

	bool isVar();
	bool isFuncCall();

	mutator getMutator();
	std::string getType();
	std::string getName();
	std::vector<Value *> getParameters();
	File *getFile();

	bool setFile(File *f);

private:
	mutator mut;
	bool var;
	bool funcCall;
	std::string type;
	std::string name;
	std::vector<Value *> parameters;

	File *file;
};
#endif
