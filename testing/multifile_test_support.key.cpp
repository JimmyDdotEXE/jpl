#include <iostream>

#include "multifile_test.h"

#include "multifile_test_support.h"


//Globals can be declared in any file, including secondary files
//Those globals can then be accessed by other files
std::string supportGlobal = "global from the support file";






//Functions can be declared in any file
void CallHelloWorld(){

	//Functions declared in other files can be called in any file
	//The function is declared in 'multifile_test.jpl'
	HelloWorld();

	return;
}



//Functions can be called from within their file, or from other files in the project.
void PrintMainGlobal(){

	//Global variables declared in other files can be accessed in any file
	//This global is declared in 'multifile_test.jpl'
	std::cout << mainGlobal << std::endl;

	return;
}
