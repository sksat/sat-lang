#ifndef AST_HPP_
#define AST_HPP_

#include <string_view>
#include <vector>
#include <memory>
#include <any>

#include "tokenizer.hpp"

namespace ast {
	using token_t = tokenizer::token_t;
	using token_iterator = std::vector<token_t>::const_iterator;

	class Base {
	public:
		Base(){}
		virtual ~Base(){}

		virtual void parse() = 0;

		token_iterator begin, end;
	};

	// 式
	class Expr : public Base {
	public:
	};

	// 即値
	class ImmExpr : public Expr {
	public:
		std::any content;
	};

	// 変数
	class VariableExpr : public Expr {
	public:
	};

	// 2項演算
	class BinaryExpr: public Expr {
	public:
		token_t operator_;
		std::shared_ptr<Expr> lhs, rhs;
	};

	// 代入
	class SubstitutionExpr : public Expr {
	public:
		std::shared_ptr<Expr> expr;
	};

	// 括弧
	class BracketsExpr : public Expr {
	public:
		std::shared_ptr<Expr> expr;
	};

	// 関数呼び出し
	class CallFuncExpr : public Expr {
	public:
		token_t name;
		std::shared_ptr<BracketsExpr> args;
	};

	// 変数定義
	// var hoge;
	// const fuga = hoge;
	class DefVariable : public Base {
	public:
		bool is_const();
		std::shared_ptr<Expr> init_expr;
	};

	// ブロック
	class Block : public Base {
	public:
		void parse();
		void parse_function(token_iterator&);

		std::shared_ptr<Block> parent;
		std::vector<std::shared_ptr<Base>> sub;
	};

	// 関数定義
	class DefFuncBlock : public Block {
	public:
		token_t name;
	};

	// ifブロック
	class IfBlock : public Block {
	public:
		std::shared_ptr<Expr> cond_expr;
		std::vector<std::shared_ptr<Block>> else_block;
	};

	// loopブロック
	class LoopBlock : public Block {
	public:
		std::shared_ptr<Expr> init_expr, cond_expr, update_expr; // for(init;cond;update){}
	};
}

#endif
