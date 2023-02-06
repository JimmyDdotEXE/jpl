#include <iostream>
#include <string>


int main(int argc, char *argv[]){
	//JPL has two text types, char and string.

	char c = 'a';	//chars represent a single character and takes 1 byte of memory
	char e = '\n';	//chars such as newline can be escaped

	std::string s = "turtles";	//strings are a collection of chars




	//JPL has string concatenation that combines text values into a string value.

	std::string concat = std::string("turtles") + std::string(1, ' ') + std::string("are") + std::string(1, ' ') + std::string("cool");	//results is the value "turtles are cool"
}
