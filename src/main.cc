#include <iostream>
#include "source.hpp"
#include "tokenizer.hpp"
#include "ast.hpp"

int main(int argc, char **argv){
	source src("test.sat");
	std::vector<tokenizer::token_t> token;
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
		const auto t = src.get_token();
		if(t.empty()) break;
		token.push_back(t);
		std::cout << t.type << "[" << t << "] ";
		if(t == ";" || t == "{" || t == "}")
			std::cout<<std::endl;
	}
	std::cout << std::endl
		<< "***********************" << std::endl << std::endl;

	global.begin = token.cbegin();
	global.end = token.cend();
	global.parse();

	return 0;
}
