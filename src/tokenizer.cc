#include "tokenizer.hpp"

tokenizer::tokenizer_t tokenizer::sat = [](std::string_view &src){
	return std::string_view();
};
