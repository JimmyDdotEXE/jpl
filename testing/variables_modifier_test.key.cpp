#include <iostream>
#include <string>


//a global variable is available in every scope
int counter = 0;
//variable modifiers can be used in conjunction
const double G = 9.81;



void incrementCounter();
int factHelper(int i);
int factorial(int i);
double verticalDistance(double initial, double time);



int main(int argc, char *argv[]){
	//JPL has three variable modifiers global, static, and const



	//counter is available here
	counter += 1;

	incrementCounter();

	//counter is still availble in this scope
	std::cout << counter << std::endl;



	//a static variable is allocated for the lifetime of the program
	//meaning a static variable maintains it's value between scope changes


	std::cout << factorial(5) << std::endl;



	//a const variable can't be changed after declaration
	const double PI = 3.14159;

	//PI can be read, but cannot be modifier now
	std::cout << PI << std::endl;




	//G can be used in the main scope
	std::cout << G << std::endl;

	std::cout << verticalDistance(5, 2) << std::endl;
}



void incrementCounter(){
	//counter is also available in the scope of this function
	counter += 1;

	return;
}



int factHelper(int i){
	//factHolder is initialized once and maintains it's value between function calls after that
	static int factHolder = 1;
	factHolder = factHolder * i;

	return factHolder;
}



int factorial(int i){
	int ret = 0;

	for(int loop1=0;loop1<i;loop1++){
		ret = factHelper(i - loop1);
	}

	return ret;
}



double verticalDistance(double initial, double time){
	//G is also available in this scope, but it cannot be changed
	return initial * time - 0.5 * G * time * time;
}
