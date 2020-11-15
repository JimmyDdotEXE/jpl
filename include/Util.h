#ifndef UTIL_H
#define UTIL_H

#include <string>
#include <vector>


std::string lower(std::string s);

bool numeric(std::string s);

std::string numString(long num);

std::vector<std::string> splitString(std::string line, char c);

#endif
