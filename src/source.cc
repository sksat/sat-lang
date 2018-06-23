#include <iostream>
#include "source.hpp"

void source::load_file(){
	std::string line;

	auto file = std::ifstream(fname);

	if(!file) std::cout<<"cannot open file"<<std::endl;

	while(file){
		std::getline(file, line);
		src_raw += line + '\n';
	}

	src = std::string_view(src_raw);
}
