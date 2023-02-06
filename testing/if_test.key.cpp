#include <iostream>
#include <string>


int main(int argc, char *argv[]){
	//JPL has if, else, and elseif statements.




	//if statements take a Cond value.
	//The body of the if statement is executed if its Cond value is True.

	if(true){
		std::cout << 0 << std::endl;
	}




	//if statements can be followed by an else statement.
	//The else statement's body is executed when the if's Cond value is False.

	if(false){
		std::cout << "from the if" << std::endl;
	}else{
		std::cout << "from the else" << std::endl;
	}




	//elseif statements can be placed between an if statement and an else statement.
	//Any number of elseif statements can be listed in a row.
	//An elseif statement's body is executed when all previous if and elseif Cond values are False and it's Cond value is True.

	if(4 > 5){
		std::cout << "from the if" << std::endl;
	}else if(false){
		std::cout << "from the first elseif" << std::endl;
	}else if(2 == 2){
		std::cout << "from the second elseif" << std::endl;
	}else{
		std::cout << "from the else" << std::endl;
	}
}
