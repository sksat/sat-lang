#include "tokenizer.hpp"

void skip_space(std::string_view &src){
	while(true){
		if(src.empty()) break;
		switch(src[0]){
			case ' ':
			case '\t':
			case '\n':
				src.remove_prefix(1);
				break;
			default:
				goto fin;
		}
	}
fin:
	return;
}

tokenizer::tokenizer_t tokenizer::sat = [](std::string_view &src){
	static std::vector<char> delim_char = {
		// 1文字で区切れるやつ
		' ', '\t', '\n',
		'[', ']',
		'{', '}',
		'(', ')',
		',', ';',
		'?'
	};
	static std::vector<std::string> delim_str = {
		"::", ":",
		"<<=", "<<", "<=", "<-",
		">>=", ">>", ">=",
		"->", "--", "-=", "-",
		"++", "+=", "+",
		"&&", "&=", "&",
		"||", "|=", "|",
		"*=", "*",
		"/=", "/",
		"%=", "%",
		"!=", "!",
		"^=", "^",
		"~=", "~",
	};

	// 空白をスキップ
	skip_space(src);

	std::string_view token;
	for(size_t i=0; i<=src.size(); i++){
		// 文字列
		if(src[i] == '\'' || src[i] == '\"'){
			if(i != 0) goto default_token;
			size_t siz;
			for(siz=1;siz<=src.size();siz++){
				if(src[siz] == '\'' || src[siz] == '\"'){
					if(src[siz-1] == '\\') continue;
					siz++;
					break;
				}
			}
			token = src.substr(0, siz);
			src.remove_prefix(siz);
			return token;
		}

		// 1文字で区切れるやつ
		for(const auto& dc : delim_char){
			if(src[i] != dc) continue;
			if(i != 0) goto default_token;
			token = src.substr(0, 1);
			src.remove_prefix(1);
			return token;
		}

		// 複数文字で区切れるやつ
		for(const auto& ds : delim_str){
			auto tmp = src.substr(i, ds.size());
			if(ds != tmp) continue;
			if(i != 0) goto default_token;
			src.remove_prefix(ds.size());
			return tmp;
		}

		// 通常時はdefault_tokenに行かない
		continue;
default_token:
		token = src.substr(0, i);
		src.remove_prefix(i);
		return token;
	}

	return src;
};
