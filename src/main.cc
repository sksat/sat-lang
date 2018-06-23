#include <iostream>
#include "source.hpp"
#include "tokenizer.hpp"

int main(int argc, char **argv){
	source src("test.sat");
	src.set_tokenizer(tokenizer::sat);

	std::cout
		<< "***** source code *****" << std::endl
		<< src.get_src()
		<< "***********************"
		<< std::endl << std::endl;

	std::cout
		<< "******** token ********" << std::endl;
	while(true){
		auto token = src.get_token();
		if(token.empty()) break;
		std::cout << "[" << token << "] ";
		if(token == ";" || token == "{" || token == "}")
			std::cout<<std::endl;
	}
	std::cout << std::endl
		<< "***********************" << std::endl << std::endl;

	return 0;
}
