#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <locale>
#include "Util.h"
#include "parser/Parser.h"
#include "constructor/Constructor.h"


/*
	main function
	the entry point of the program
*/
int main(int argc, char *argv[]){
	bool error = false;

	for(int i=1;i<argc;i++){
		//open argv[i] file
		std::string arg(argv[i]);
		std::string out = splitString(arg, '.')[0] + ".cpp";
		std::ifstream src;
		src.open(arg.c_str());

		//if the src file successfully opened
		if(src.is_open()){
			std::ofstream dest;

			std::vector<std::string> input;
			std::vector<std::string> output;

			//get all lines from src file and place them in a std::vector<std::string>
			std::string line;
			while(getline(src, line)){
				input.push_back(line);
			}

			//try-catch to catch errors in parser and constructor functions
			try{
				//run the lines from the src file through the parser function
				//run the parser output through the constructor function
				//save constructor output to output std::vector<std::string>
				output = constructor(parser(input));

				//open dest file if there have been no errors
				dest.open(out.c_str());

			}catch(const std::exception&){
				//close src file and return EXIT_FAILURE if an exception is caught
				src.close();

				std::cout << "Error caught" << std::endl;

				return EXIT_FAILURE;
			}

			//write output to new file
			for(int x=0;x<output.size();x++){
				dest << output.at(x) + "\n";
			}

			//close both src and dest files
			src.close();
			dest.close();

		//error message if input file can't be found
		}else{
			std::cout << "File " << arg << " missing or not found." << std::endl;
		}
	}
}
