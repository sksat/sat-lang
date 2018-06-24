#include <iostream>
#include "source.hpp"
#include "tokenizer.hpp"
#include "ast.hpp"

int main(int argc, char **argv){
	source src("test.sat");
	ast::Block global;

	src.set_tokenizer(tokenizer::sat);

	std::cout
		<< "***** source code *****" << std::endl
		<< src.get_src()
		<< "***********************"
		<< std::endl << std::endl;

	std::cout
		<< "******** token ********" << std::endl;
	while(true){
		const auto token = src.get_token();
		if(token.empty()) break;

		global.tokens.push_back(token);
		std::cout << token.type << "[" << token << "] ";
		if(token == ";" || token == "{" || token == "}")
			std::cout<<std::endl;
	}
	std::cout << std::endl
		<< "***********************" << std::endl << std::endl;

	global.parse();

	return 0;
}
