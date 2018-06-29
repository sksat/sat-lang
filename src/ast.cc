#include <iostream> // TODO: debug only
#include <utility>
#include "ast.hpp"

namespace ast {
	void Expr::parse(){
		auto it = begin;
		std::cout<<"expr[[ ";
		while(it!=end){
			std::cout<<*it<<" ";
			it++;
		}
		std::cout<<"]]"<<std::endl;
	}

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
				parse_function(it);
				break;
			case type::If:
			case type::Loop:
			case type::Delim:
			case type::Import:
			case type::Return:
				return;
				break;
			// expr
			default:
				parse_expr(it);
				break;
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
						std::cout<<*hoge<<" ";
					std::cout<<" ]"<<std::endl;
				}
				break;
			}
		}
	}

	void Block::parse_expr(token_iterator &it){
		using type = tokenizer::type_t;
		auto expr = std::make_shared<Expr>();
		expr->begin = it;
		while(it!=end){
			it++;
			if(it->type==type::Delim && *it==";"){
				expr->end = it;
				break;
			}
		}
		expr->parse();
		sub.push_back(expr);
	}

	// itはFunction tokenの状態で呼ばれる
	void Block::parse_function(token_iterator &it){
		auto func = std::make_shared<DefFuncBlock>();

		it++;
		func->name = *it; // 関数名
		it++; if(*it != "(") std::cerr<<"function error"<<std::endl;

		// 引数を取ってくる
		auto args = std::make_pair(it, it);
		while(it!=end){
			it++;
			if(*it != ")"){
				args.second = it;
				break;
			}
		}

		// 返り値の型
		if(*it == "<-"){
			std::cerr<<"<- is not implemented."<<std::endl;
			it++;
		}

		if(*it != "{") std::cerr<<"func error"<<std::endl;
		it++;

		func->begin = it;
		while(it!=end){
			it++;
			if(*it == "}"){
				func->end = it;
				break;
			}
		}

		std::cout << "function def:" << std::endl
			<< "name: " << func->name << std::endl
			<< "args: ";
		for(auto i=args.first; i!=args.second; i++){
			std::cout << *i << " ";
		}
		std::cout << std::endl;
		func->parse();

		sub.push_back(func);
	}
}
