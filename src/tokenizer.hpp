#ifndef TOKEN_HPP_
#define TOKEN_HPP_

#include <vector>
#include "source.hpp"

class tokenizer {
public:
	using token_t = source::token_t;
	using tokenizer_t = source::tokenizer_t;

	enum type_t {
		Unknown,
		Delim,
		Identifier,
		String,
		Decimal,
		Hex,
		Octal,
		Operator,
		Function,
		If,
		Loop,
	};

	static tokenizer_t sat;
};

#endif
