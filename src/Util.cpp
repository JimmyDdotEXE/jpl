#include <sstream>
#include <algorithm>
#include <locale>
#include "Util.h"


/*takes a string and returns that string with all lower-case letters*/
std::string lower(std::string s){
	std::locale loc;
	std::string ret = "";

	for(int i=0;i<s.length();i++){
		ret += tolower(s[i], loc);
	}

	return ret;
}


/*takes a string and returns true or false if it's a number*/
bool numeric(std::string s){
	std::locale loc;

	bool neg = false;
	bool dec = false;

	for(int i=0;i<s.length();i++){
		if(!isdigit(s[i], loc)){
			if(s[i] == '.' && !dec){
				dec = true;
			}else if(s[i] == '-' && !neg){
				neg = true;
			}else{
				return false;
			}
		}
	}

	return true;
}


/*takes a long and return it as a string*/
std::string numString(long num){
	std::ostringstream stream;
	stream << num;

	return stream.str();
}


/*
	takes a std::string and char as parameters
	splits the given string into substrings at each occurence of the given char
	returns a std::vector<std::string> containing all substrings
*/
std::vector<std::string> splitString(std::string line, char c){
	std::vector<std::string> ss;

	while(1){
		//find first occurence of given char
		size_t pos = line.find(c);

		//if the string is empty, leave the loop
		if(line == ""){
			break;

		//if the char doesn't occur, add the whole string to the return value and leave the loop
		}else if(pos == std::string::npos){
			ss.push_back(line);
			break;

		//if the given char is not the first char of the given string
		}else if(pos != 0){

			//variables for if the function is allowed to split the string and if the loops should continue
			bool allow = true;
			bool cont = true;

			//loop while double quotes are being found and cont is true
			size_t firstQuote = 0;
			while((firstQuote = line.find('\"', firstQuote ? firstQuote+1 : firstQuote)) != std::string::npos && cont){
				
				//if the first quote found isn't at the begining, make sure it's not escaped
				if(firstQuote != 0){
					if(line[firstQuote-1] == '\\'){
						continue;
					}
				}


				//loop while double quotes are biong found and cont is true
				size_t secondQuote = firstQuote;
				while((secondQuote = line.find('\"', secondQuote+1)) != std::string::npos && cont){

					//make sure the located double quote isn't escaped
					if(secondQuote != 0){
						if(line[secondQuote-1] == '\\'){
							continue;
						}
					}

					//if the position of the given char is between firstQuote and secondQuote
					//split at the second double quote instead of the found position
					if(pos > firstQuote && pos < secondQuote){
						ss.push_back(line.substr(0, secondQuote+1));
						line = line.substr(secondQuote+1);
						allow = false;
					}else{
						allow = true;
					}

					cont = false;
				}
			}



			//set cont back to true
			cont = true;

			//loop while quotes are being found and cont and allow are both true
			firstQuote = 0;
			while((firstQuote = line.find('\'', firstQuote ? firstQuote+1 : firstQuote)) != std::string::npos && cont && allow){
				
				//if the first quote found isn't at the begining, make sure it's not escaped
				if(firstQuote != 0){
					if(line[firstQuote-1] == '\\'){
						continue;
					}
				}


				//loop while quotes are being found and cont is true
				size_t secondQuote = firstQuote;
				while((secondQuote = line.find('\'', secondQuote+1)) != std::string::npos && cont){

					//make sure the located quote isn't escaped
					if(secondQuote != 0){
						if(line[secondQuote-1] == '\\'){
							continue;
						}
					}

					//if the position of the given char is between firstQuote and secondQuote
					//split at the second quote instead of the found position
					if(pos > firstQuote && pos < secondQuote){
						ss.push_back(line.substr(0, secondQuote+1));
						line = line.substr(secondQuote+1);
						allow = false;
					}else{
						allow = true;
					}

					cont = false;
				}
			}


			//if the function is allowed split the string at the found position
			if(allow){
				ss.push_back(line.substr(0, pos));
				line = line.substr(pos+1);
			}
		}else{
			line = line.substr(pos+1);
		}
	}

	return ss;
}


bool between(std::vector<pair_t> matches, int index, size_t pos){

	for(int i=0;i<matches.size();i++){

		if(index > matches.at(i).openStr && index < matches.at(i).closeStr){
			return true;

		}else if(index >= matches.at(i).openStr && index < matches.at(i).closeStr){
			if(pos > matches.at(i).openPos){
				return true;
			}

		}else if(index > matches.at(i).openStr && index <= matches.at(i).closeStr){
			if(pos < matches.at(i).closePos){
				return true;
			}

		}else if(index >= matches.at(i).openStr && index <= matches.at(i).closeStr){
			if(pos > matches.at(i).openPos && pos < matches.at(i).closePos){
				return true;
			}
		}
	}

	return false;
}
