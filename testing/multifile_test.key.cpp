#include <iostream>

#include "multifile_test_support.h"

#include "multifile_test.h"


//Global variables can be declared in any file, including the main file
//Those globals can then be accessed by other files
std::string mainGlobal = "global from the main file";



int main(int argc, char *argv[]){
	//JPL supports projects that span multiple files

	//This is the main file of this example and is supported by 'multifile_test_support.jpl'



	//Global variables declared in other files can be accessed in any file
	//This global is declared in 'multifile_test_supprt.jpl'
	std::cout << supportGlobal << std::endl;


	//Functions declared in other files can be accessed in any file
	//This function is declared in 'multifile_test_supprt.jpl'
	PrintMainGlobal();

	//This function is also declared in 'multifile_test_supprt.jpl'
	CallHelloWorld();
}



//Functions can be declared in any file
//Those functions can then be called in other files
void HelloWorld(){
	std::cout << "Hello World!" << std::endl;

	return;
}
