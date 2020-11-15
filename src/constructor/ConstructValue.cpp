#include "value/Num.h"
#include "value/Cond.h"
#include "value/Text.h"
#include "constructor/ConstructNum.h"
#include "constructor/ConstructCond.h"
#include "constructor/ConstructText.h"
#include "constructor/ConstructValue.h"


/*
	constructValue function
	takes a Value pointer as parameter
	builds a C++ value based on parameter
	returns a std::string
*/
std::string constructValue(Value *in){

	if(Num *v = dynamic_cast<Num *>(in)){
		return constructNum(v);
	}else if(Cond *v = dynamic_cast<Cond *>(in)){
		return constructCond(v);
	}else if(Text *v = dynamic_cast<Text *>(in)){
		return constructText(v);
	}

	return "";
}
