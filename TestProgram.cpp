#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <stdlib.h>


void system(std::string s){
	system(s.c_str());
}


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


bool testFile(std::string f){
	std::ifstream file;
	std::ifstream output;
	std::ifstream key;

	file.open(f);
	if(file.is_open()){
		system("./jpl " + f);

		output.open(splitString(f, '.')[0] + ".cpp");
		key.open(splitString(f, '.')[0] + ".key.cpp");

		if(output.is_open() && key.is_open()){
			std::string line1;
			std::string line2;

			bool errorFound = false;

			while(1){
				bool outputFound = (bool)getline(output, line1);
				bool keyFound = (bool)getline(key, line2);

				if(!outputFound && !keyFound){
					break;
				}else if(outputFound != keyFound){
					errorFound = true;
					std::cout << "check " + splitString(f, '.')[0] + ".cpp" << std::endl;
					break;
				}else if(line1 != line2){
					errorFound = true;
					std::cout << "check " + splitString(f, '.')[0] + ".cpp" << std::endl;
				}
			}

			output.close();
			key.close();

			if(!errorFound){
				system("rm " + splitString(f, '.')[0] + ".cpp");
			}
		}

		file.close();
	}else{
		std::cout << "File " + f + " not found." << std::endl;
	}

	return true;
}

bool testFiles(std::vector<std::string> f){
	bool fileMissing = false;
	std::string jplParameters = "";

	for(int i=0;i<f.size();i++){
		std::ifstream file(f.at(i));

		jplParameters += " " + f.at(i);

		if(!file.is_open()){
			std::cout << "File " + f.at(i) + " missing or not found." << std::endl;
			fileMissing = true;
		}else{
			file.close();
		}
	}

	if(fileMissing){
		return false;
	}


	system("./jpl" + jplParameters);


	for(int i=0;i<f.size();i++){
		std::ifstream output(splitString(f.at(i), '.')[0] + ".cpp");
		std::ifstream key(splitString(f.at(i), '.')[0] + ".key.cpp");

		if(output.is_open() && key.is_open()){
			std::string line1;
			std::string line2;

			bool errorFound = false;

			while(1){
				bool outputFound = (bool)getline(output, line1);
				bool keyFound = (bool)getline(key, line2);

				if(!outputFound && !keyFound){
					break;
				}else if(outputFound != keyFound){
					errorFound = true;
					std::cout << "check " + splitString(f.at(i), '.')[0] + ".cpp" << std::endl;
					break;
				}else if(line1 != line2){
					errorFound = true;
					std::cout << "check " + splitString(f.at(i), '.')[0] + ".cpp" << std::endl;
				}
			}

			output.close();
			key.close();

			if(!errorFound){
				system("rm " + splitString(f.at(i), '.')[0] + ".cpp");
			}
		}

		output.open(splitString(f.at(i), '.')[0] + ".h");
		key.open(splitString(f.at(i), '.')[0] + ".key.h");

		if(output.is_open() && key.is_open()){
			std::string line1;
			std::string line2;

			bool errorFound = false;

			while(1){
				bool outputFound = (bool)getline(output, line1);
				bool keyFound = (bool)getline(key, line2);

				if(!outputFound && !keyFound){
					break;
				}else if(outputFound != keyFound){
					errorFound = true;
					std::cout << "check " + splitString(f.at(i), '.')[0] + ".h" << std::endl;
					break;
				}else if(line1 != line2){
					errorFound = true;
					std::cout << "check " + splitString(f.at(i), '.')[0] + ".h" << std::endl;
				}
			}

			output.close();
			key.close();

			if(!errorFound){
				system("rm " + splitString(f.at(i), '.')[0] + ".h");
			}
		}
	}

	return true;
}


int main(int argc, char *argv[]){
	std::vector<std::string> files{
		"testing/cond_test.jpl",
		"testing/functions_test.jpl",
		"testing/if_test.jpl",
		"testing/loops_test.jpl",
		"testing/num_test.jpl",
		"testing/print_test.jpl",
		"testing/text_test.jpl",
		"testing/variables_modifier_test.jpl",
		"testing/variables_test.jpl"
	};

	std::vector<std::vector<std::string>> multiFiles{
		{
			"testing/multifile_test.jpl",
			"testing/multifile_test_support.jpl"
		}
	};

	for(int i=0;i<files.size();i++){
		testFile(files.at(i));
	}

	for(int i=0;i<multiFiles.size();i++){
		testFiles(multiFiles.at(i));
	}
}
