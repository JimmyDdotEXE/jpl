#include "statement/Print.h"


Print::Print(Value *v){
	value = v;
}


Value *Print::getValue(){
	return value;
}
