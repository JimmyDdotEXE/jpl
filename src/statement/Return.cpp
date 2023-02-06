#include "statement/Return.h"


Return::Return(Value *v){
	value = v;
}


Value *Return::getValue(){
	return value;
}
