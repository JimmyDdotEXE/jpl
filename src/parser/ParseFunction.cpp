#include <iostream>
#include <climits>
#include "parser/Parser.h"
#include "parser/ParseValue.h"
#include "Util.h"
#include "parser/ParseFunction.h"


std::vector<Function *> parseFunctions(std::vector<std::string> *in){
	std::vector<Function *> ret;
	std::vector<std::string> comments;
	int emptyLines = 0;

	//read next line from file
	for(int j=0;j < in->size();j++){
		std::string line = in->at(j);
		std::string comment = "";


		//look for a comment in the current line
		size_t cPos = line.find('#');
		if(cPos != std::string::npos){
			comment = line.substr(cPos+1);
			line = line.substr(0, cPos);
		}

		int numTabs = 0;

		//count the tab depth of the line
		for(int i=0;line[i] == '\t';i++){
			numTabs++;
		}

		if(numTabs != 0){
			continue;
		}


		//split the line into strings separated by tabs
		std::vector<std::string> temp = splitString(line, '\t');
		std::vector<std::string> ss;

		//if there were any strings resulting from the last split
		if(temp.size()){
			//split the first string again by spaces this time
			ss = splitString(temp.at(0), ' ');
		}

		/*
		 * due to how these two calls to splitString() are used,
		 * the language requires tabs instead of spaces for indentation
		 * and tabs should not be used in the main statement of the line
		 * tabs are safe to use in comments and to separate a comment from a statement
		 */


		if(ss.size() == 0 && comment == ""){
			if(comments.size()){
				comments.clear();
				emptyLines = 0;
			}

			emptyLines++;
		}else if(ss.size() == 0 && comment != ""){
			comments.push_back(comment);
		}


		//for each line in ss
		for(int i=0;i<ss.size();i++){
			//look for the terminal character ':'
			size_t term = ss.at(i).find(':');

			//if no terminal character is found, continue
			if(term == std::string::npos){
				if(i == ss.size()-1){
					emptyLines = 0;
				}

				continue;
			}

			std::vector<std::string> lhs;

			//add all strings on the left of the terminal character to lhs vector
			for(int x=0;x<ss.size();x++){
				if(x<i){
					lhs.push_back(ss.at(x));
				}
			}

			//add all characters left of terminal character to lhs vector as a string
			if(ss.at(i).substr(0, term) != ""){
				lhs.push_back(ss.at(i).substr(0, term));
			}

			//if the return type is known, parse the function
			if(lookupType(lhs.at(0))){
				Function *tmp = new Function();

				std::vector<std::string> holder;
				std::vector<Value *> params;


				//for every space-separated string to the left of the terminal character
				for(int x=0;x<lhs.size();x++){

					//the first string of the function header should be the type
					if(x == 0){

						//if that return type is know, the tmp function's type is set
						if(lookupType(lhs.at(x))){
							tmp->setType(lhs.at(x));

						//else it's an error
						}else{
							std::cout << "Undefined type \'" << lhs.at(x) << "\'." << std::endl;
							throw std::exception();
						}

					//the second string of the function header should me the function name
					}else if(x == 1){

						//if the opening parenthesis is right up against the function name
						if(lhs.at(x).find('(') != std::string::npos){
							//find the opening parenthesis
							size_t pos = lhs.at(x).find('(');

							if(lhs.at(x).substr(pos+1) == ""){
								lhs.at(x) = lhs.at(x).substr(0, pos);
							}else{
								lhs.insert(lhs.begin()+x+1, lhs.at(x).substr(pos+1));
								lhs.at(x) = lhs.at(x).substr(0, pos);
							}
						}
					
						if(nameCheck(lhs.at(x))){
							tmp->setName(lhs.at(x));
						}


					//if a parameter-separating comma is found in the current string
					}else if(lhs.at(x).find(',') != std::string::npos){
						size_t pos = lhs.at(x).find(',');

						if(lhs.at(x).length() == 1){
							lhs.erase(lhs.begin()+x);
							x--;
						}else if(lhs.at(x).substr(0, pos) == ""){
							lhs.at(x) = lhs.at(x).substr(pos+1);
							x--;
						}else if(lhs.at(x).substr(pos+1) == ""){
							lhs.at(x) = lhs.at(x).substr(0, pos);
							holder.push_back(lhs.at(x));
						}else{
							lhs.insert(lhs.begin()+x+1, lhs.at(x).substr(pos+1));
							lhs.at(x) = lhs.at(x).substr(0, pos);
							holder.push_back(lhs.at(x));
						}

						if(Value *v = parseDeclarationVar(holder)){
							params.push_back(v);
							holder.clear();
							continue;
						}else{
							//TODO: what goes here?
						}


					//if the closing parenthesis is found in the current string
					}else if(lhs.at(x).find(')') != std::string::npos){
						size_t pos = lhs.at(x).find(')');

						if(lhs.at(x).length() == 1){
							break;
						}else if(lhs.at(x).substr(0, pos) == ""){
							lhs.at(x) = lhs.at(x).substr(pos+1);
							x--;
						}else if(lhs.at(x).substr(pos+1) == ""){
							lhs.at(x) = lhs.at(x).substr(0, pos);
							holder.push_back(lhs.at(x));
						}else{
							lhs.insert(lhs.begin()+x+1, lhs.at(x).substr(pos+1));
							lhs.at(x) = lhs.at(x).substr(0, pos);
							holder.push_back(lhs.at(x));
						}

						if(Value *v = parseDeclarationVar(holder)){
							params.push_back(v);
							holder.clear();
							break;
						}else{
							//TODO: what goes here?
						}

					//if the current string isn't a type, name, parenthesis, or comma
					//it's a variable that gets added to the holder vector
					}else{
						holder.push_back(lhs.at(x));
					}
				}


				int lastLive = j;
				int emptyAfter = 1;
				int commentLocation = INT_MAX;
				bool done = false;

				//for each string in the input vector past the function header
				for(int k=j+1;k<in->size();k++){

					int tabs = 0;


					//if the current string is empty, the running total of empty lines is incremented
					if(in->at(k).length() == 0){
						emptyAfter++;
					}


					//for each character in the current string
					for(int l=0;l<in->at(k).length();l++){

						//if the current character is a tab, the tab count is increased
						if(in->at(k)[l] == '\t'){
							tabs++;

						//if the current character is not a pound sign, it's not a comment
						}else if(in->at(k)[l] != '#'){

							//if there are any tabs in front of the line, it is a live line
							if(tabs > 0){
								lastLive = k;
								emptyAfter = 1;
								commentLocation = INT_MAX;

							//if there are no tabs,
							}else{
								done = true;
								break;
							}

						//if the current character is anything else, leave the loop
						}else{
							commentLocation = k - lastLive;
							break;
						}
					}

					if(done){
						break;
					}
				}

				std::vector<std::string> lines;
				for(int k=j+1;k<=lastLive;k++){
					lines.push_back(in->at(k));
				}

				tmp->setParameters(params);
				tmp->setTemp(lines);
				tmp->setSideComment(comment);
				tmp->setTopComment(comments);
				in->erase(in->begin()+j-comments.size()-emptyLines, in->begin()+j+lines.size()+1);
			
				j -= comments.size()+emptyLines+1;

				ret.push_back(tmp);

				comments.clear();
				emptyLines = 0;
			}else{
				break;
			}
		}

		clearScope();
	}

	return ret;
}
