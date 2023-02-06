#ifndef UTIL_H
#define UTIL_H

#include <string>
#include <vector>
#include "File.h"


typedef struct{
	int openStr;
	size_t openPos;
	int closeStr;
	size_t closePos;
} pair_t;


extern std::vector<std::string> types;

extern std::vector<std::string> reservedNames;

extern File *currentFile;


std::string lower(std::string s);

bool numeric(std::string s);

std::string numString(long num);

std::vector<std::string> splitString(std::string line, char c);

bool between(std::vector<pair_t> matches, int index, size_t pos);

#endif
