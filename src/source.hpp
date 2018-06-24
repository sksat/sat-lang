#ifndef SOURCE_HPP_
#define SOURCE_HPP_

#include <string>
#include <string_view>
#include <fstream>
#include <functional>

class source {
public:
	source(){}
	source(const std::string &fname){
		this->fname = fname;
		load_file();
	}

	void load_file();

	using token_t = std::string_view;
	using tokenizer_t = std::function<token_t(std::string_view&)>;

	void set_tokenizer(tokenizer_t t){
		tokenizer = t;
	}

	std::string_view get_raw(){ return std::string_view(src_raw); }
	std::string_view& get_src(){ return src; }

	token_t get_token(tokenizer_t t){
		return t(src);
	}
	token_t get_token(){
		return get_token(tokenizer);
	}
private:
	std::string fname;
	std::string src_raw;
	std::string_view src;

	tokenizer_t tokenizer;
};

#endif
