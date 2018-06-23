#include <iostream>
#include "source.hpp"
#include "tokenizer.hpp"

int main(int argc, char **argv){
	source src("test.sat");

	std::cout
		<< "***** source code *****"
		<< std::endl
		<< src.get_src()
		<< "***********************"
		<< std::endl << std::endl;

	src.set_tokenizer(tokenizer::sat);

	while(true){
		auto token = src.get_token();
		if(token.empty()) break;
		std::cout << "[" << token << "]" << std::endl;
	}

	return 0;
}
