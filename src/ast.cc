#include <iostream> // TODO: debug only
#include <utility>
#include "ast.hpp"

namespace ast {
	// 式
	// Decimal,String
	// var: Identifier
	// func: Identifier()
	void Expr::parse(){
		using type = tokenizer::type_t;

		auto it = begin;
		std::cout<<"expr[[ ";
		while(it!=end){
			std::cout<<*it<<" ";
			it++;
		}
		std::cout<<"]]"<<std::endl;

		it = begin;

		std::vector<std::shared_ptr<Expr>> subexpr;
		while(it!=end){
			if(it->type == type::Decimal || it->type == type::String){
				auto imm = std::make_shared<ImmExpr>();
				imm->begin = imm->end = it;
				imm->end++;
				subexpr.push_back(imm);
			}else if(it -> type == type::Identifier){
				if(*(it+1) == "("){
					auto fncall = std::make_shared<CallFuncExpr>();
					fncall->begin = it;
					fncall->name = *it;
					it++;
					fncall->args->begin = it;
					while(*it!=")") it++;
					fncall->end = fncall->args->end = it;
					subexpr.push_back(fncall);
				}
			}else if(it->type == type::Operator){
			}else throw;
			it++;
		}
		for(const auto &e : subexpr){
			std::cout<<"("<<e->to_src()<<")";
		}
		std::cout<<std::endl;
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
