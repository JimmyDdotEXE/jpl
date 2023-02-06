#include <iostream>
#include <string>


int factorial(int i);
void printCats(int i);



int main(int argc, char *argv[]){
	// JPL supports functions.


	//Functions can be called to exacute their logic and return a value.
	int fact5 = factorial(5);


	//Functions can be placed anywhere in a file as long as it is the first file of the project.
	printCats();
}



// Functions can have any JPL type such as int.
int factorial(int i){
	if(i == 1){
		return i;
	}else{
		return i * factorial(i - 1);
	}

	return 1;
}



//Functions don't have to have a return type.
//Pure logic functions with no return value have the type 'none'.
void printCats(int i){
	std::string cats = "";

	for(int loop1=0;loop1<i;loop1++){
		cats = cats + std::string("cats");
	}

	std::cout << cats << std::endl;

	return;
}
