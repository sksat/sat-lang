#include <iostream> // TODO: debug only
#include <utility>
#include "ast.hpp"

namespace ast {
	// ブロック中のコードの種類
	// 式: "なんちゃらかんちゃら;"
	// if/loop文: "if () {}"
	// 関数定義: "fn hoge() <- {}"
	// 変数定義: "var fuga;"
	void Block::parse(){
		using type = tokenizer::type_t;

		for(auto it=begin; it!=end; it++){
			switch(it->type){
			case type::Function:
				{
					it++; auto name = *it;
					it++; if(*it != "(") std::cerr<<"func error"<<std::endl;
					auto args = std::make_pair(it, it);
					while(it!=end){
						it++;
						if(*it == ")"){
							args.second = it;
							break;
						}
					}
					it++; if(*it == "<-"){
						std::cerr<<"<- is not implemented"<<std::endl;
						return;
					}
					if(*it != "{") std::cerr<<"func err"<<std::endl;
					it++;
					auto blk = std::make_pair(it, it);
					while(it!=end){
						it++;
						if(*it == "}"){
							blk.second = it;
							break;
						}
					}

					{
						std::cout<<"function def"<<std::endl
							<< "name:\t" << name << std::endl;
						for(auto tmp=blk.first; tmp!=blk.second; tmp++){
							std::cout<<*tmp<<" ";
						}
					}
				}
				break;
			case type::If:
			case type::Loop:
			case type::Delim:
				return;
				break;
			default:
				{
					auto sub = std::make_pair(it, it);
					while(it!=end){
						it++;
						if(it->type == type::Delim && *it==";"){
							sub.second = it;
							break;
						}
					}
					std::cout<<"expr[ ";
					for(auto hoge=sub.first; hoge!=sub.second; hoge++)
						std::cout<<*hoge;
					std::cout<<" ]"<<std::endl;
				}
				break;
			}
		}
	}
}
