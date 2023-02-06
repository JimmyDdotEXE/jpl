#include <iostream>
#include <string>


int main(int argc, char *argv[]){
	//JPL has two types of loops know as for loops and while loops.


	//For loops take a Num value and iterate from 0 to the given number.

	for(int loop1=0;loop1<5;loop1++){
		//'loop' is a variable within the scope of the for loop that acts as the iterator for that loop
		std::cout << loop1 << std::endl;
	}

	//For loops are nestable.

	for(int loop1=0;loop1<3;loop1++){
		std::cout << "" << std::endl;

		for(int loop2=0;loop2<3;loop2++){
			//and 'loop' is always the iterator for the most recent loop
			std::cout << loop2 << std::endl;
		}
	}


	//While loops take a Cond value and continue to run while that value is true.

	int i = 0;
	while(i < 4){
		std::cout << i << std::endl;
		i += 1;
	}

	//While loops are also nestable.

	int x = 0;
	while(x < 3){
		std::cout << "" << std::endl;

		int y = 3;

		while(y > 0){
			std::cout << y << std::endl;
			y -= 1;
		}

		x += 1;
	}
}
