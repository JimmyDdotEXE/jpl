#include <algorithm>
#include "statement/Function.h"
#include "File.h"


/*File class constructor*/
File::File(std::string s){
	size_t pos = s.find_last_of("/\\");

	if(pos != std::string::npos){
		path = s.substr(0, pos);
	}else{
		path = ".";
	}

	name = s.substr(pos+1);
}


/*returns the name of the file*/
std::string File::getName(){
	return name;
}

/*returns the path of the file*/
std::string File::getPath(){
	return path;
}

/*returns the function pointers in the file*/
std::vector<Function *> File::getFunctions(){
	return functions;
}

/*returns global structures for the file*/
std::vector<global_t> File::getGlobals(){
	return globals;
}

/*returns all the inclusions the file uses*/
std::vector<File *> File::getInclusions(){
	return includes;
}

/*returns a lines of JPL code without functions or globals*/
std::vector<std::string> File::getHolder(){
	return holder;
}

/*returns lines that have been parsed*/
std::vector<line_t> File::getLines(){
	return lines;
}


/*sets the name of the file*/
bool File::setName(std::string s){
	name = s;

	return name == s;
}

/*sets the path of the file*/
bool File::setPath(std::string s){
	path = s;

	return path == s;
}

/*sets the vector of function pointers*/
bool File::setFunctions(std::vector<Function *> f){
	functions = f;

	for(int i=0;i<functions.size();i++){
		functions.at(i)->file = this;
	}

	return true;
}

/*sets the vector of globals in the */
bool File::setGlobals(std::vector<global_t> g){
	globals = g;

	for(int i=0;i<globals.size();i++){
		globals.at(i).assignment->getLeft()->setFile(this);
	}

	return true;
}

/*sets the holder of JPL lines without functions or globals*/
bool File::setHolder(std::vector<std::string> s){
	holder = s;

	return true;
}

/*sets the vector of parsed lines*/
bool File::setLines(std::vector<line_t> l){
	lines = l;

	return true;
}


/*adds a to the list of inclusions that the file uses*/
bool File::addInclusion(File *f){
	if(std::find(includes.begin(), includes.end(), f) == includes.end()){
		includes.push_back(f);

		return true;
	}

	return false;
}
