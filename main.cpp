#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <locale>
#include "Util.h"
#include "File.h"
#include "parser/Parser.h"
#include "constructor/Constructor.h"
#include "parser/ParseValue.h"
#include "parser/ParseFunction.h"


//vector of reserved keywords in JPL
std::vector<std::string> reservedNames{"global", "static", "const", "for", "while", "if", "elseif", "else"};

//vector of types available in JPL
std::vector<std::string> types{"none", "byte", "short", "int", "long", "decimal", "bool", "char", "string"};

//vector of reserved keywords in C++
std::vector<std::string> cppReservedNames{
	"alignas",
	"alignof",
	"and",
	"and_eq",
	"asm",
	"atomic_cancel",
	"atomic_commit",
	"atomic_noexcept",
	"auto",
	"bitand",
	"bitor",
	"bool",
	"break",
	"case",
	"catch",
	"char",
	"char16_t",
	"char32_t",
	"class",
	"compl",
	"concept",
	"const",
	"constexpr",
	"const_cast",
	"continue",
	"co_await",
	"co_return",
	"co_yield",
	"decltype",
	"default",
	"delete",
	"do",
	"double",
	"dynamic_cast",
	"else",
	"enum",
	"explicit",
	"export",
	"extern",
	"false",
	"float",
	"for",
	"friend",
	"goto",
	"if",
	"import",
	"inline",
	"int",
	"long",
	"module",
	"mutable",
	"namespace",
	"new",
	"noexcept",
	"not",
	"not_eq",
	"nullptr",
	"operator",
	"or",
	"or_eq",
	"private",
	"protected",
	"public",
	"register",
	"reinterpret_cast",
	"requires",
	"return",
	"short",
	"signed",
	"sizeof",
	"static",
	"static_assert",
	"static_cast",
	"struct",
	"switch",
	"synchronized",
	"template",
	"this",
	"thread_local",
	"throw",
	"true",
	"try",
	"typedef",
	"typeid",
	"typename",
	"union",
	"unsigned",
	"using",
	"virtual",
	"void",
	"volatile",
	"wchar_t",
	"while",
	"xor",
	"xor_eq"
};


//set the current file to NULL
File *currentFile = NULL;


/*
	main function
	the entry point of the program
*/
int main(int argc, char *argv[]){
	//add JPL types and C++ reserved names to the reservedNames vector
	reservedNames.insert(reservedNames.end(), types.begin(), types.end());
	reservedNames.insert(reservedNames.end(), cppReservedNames.begin(), cppReservedNames.end());


	int firstFile = 1;

	if(argc >= 2){
		std::string arg(argv[1]);

		if(arg == "-v"){
			std::cout << "jpl 0.2.0" << std::endl;
			firstFile = 2;
		}
	}


	try{
		std::vector<File *> files;

		for(int i=firstFile;i<argc;i++){
			//open argv[i] file
			std::string arg(argv[i]);
			std::ifstream src;
			src.open(arg.c_str());

			File *f = new File(splitString(arg, '.')[0]);

			//if the src file successfully opened
			if(src.is_open()){
				std::vector<std::string> input;

				//get all lines from src file and place them in a std::vector<std::string>
				std::string line;
				while(getline(src, line)){
					input.push_back(line);
				}

				f->setGlobals(parseGlobals(&input));
				f->setFunctions(parseFunctions(&input));
				f->setHolder(input);

				files.push_back(f);

			//error message if input file can't be found
			}else{
				std::cout << "File " << arg << " missing or not found." << std::endl;
			}

			src.close();
		}


		parser(files);
		std::vector<File *> headers = constructor(files);

		for(int i=0;i<files.size();i++){
			std::ofstream dest(files.at(i)->getPath() + "/" + files.at(i)->getName() + ".cpp");
			std::vector<std::string> lines = files.at(i)->getHolder();

			for(int j=0;j<lines.size();j++){
				dest << lines.at(j) + "\n";
			}

			dest.close();
		}

		for(int i=0;i<headers.size();i++){
			std::ofstream dest(headers.at(i)->getPath() + "/" + headers.at(i)->getName() + ".h");
			std::vector<std::string> lines = headers.at(i)->getHolder();

			for(int j=0;j<lines.size();j++){
				dest << lines.at(j) + "\n";
			}

			dest.close();
		}


	}catch(const std::exception&){
		return EXIT_FAILURE;
	}
}
