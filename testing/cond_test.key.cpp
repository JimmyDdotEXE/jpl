#include <iostream>
#include <string>


int main(int argc, char *argv[]){
	//JPL has one conditonal type know as bool that takes 1 byte of memory.

	bool t = true;	//bools can be True
	bool f = false;	//or False

	//True and False keywords are type sensative.




	//JPL has comparison operators.

	bool eq = 2 + 3 == 5;	//== checks if any two values are equivalent
	bool neq = "turtles" != "dogs";	//!= checks if any two values are not equivalent

	bool less = 1 < 2;	//< checks if one num value is less than another
	bool great = 3 > 4;	//> checks if one num value is greater than another

	bool lessEq = 5 <= 6;	//<= checks if one num value is less than or equal to another
	bool greatEq = 7 >= 8;	//>= checks if one num value is greater than or equal to another




	//JPL has logical operators.

	bool _and_ = true && false;	//evaluates to True if both cond values are True
	bool _or_ = true || false;	//evaluates to True if either cond value is True




	//JPL has conditional negation.

	bool negated = !true;	//this has a value of False




	//JPL has conditional grouping.

	bool group = !(true && false);	//the conditional value in the parenthesis will be evaluated first and then it is negated resulting in True

	bool noGroup = !true && false;	//without grouping it evaluates to False
}
