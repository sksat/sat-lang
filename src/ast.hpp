#ifndef AST_HPP_
#define AST_HPP_

#include <string_view>
#include <vector>
#include <memory>
#include <any>

#include "tokenizer.hpp"

namespace ast {
	using token_t = tokenizer::token_t;

	class Base {
	public:
		virtual void parse() = 0;

		std::vector<token_t> token;
	};

	// 式
	class Expr : public Base {
	public:
	};

	// 即値
	class ImmExpr : public Expr {
	public:
		void parse();

		std::any content;
	};

	// 変数
	class VariableExpr : public Expr {
	public:
		void parse();
	};

	// 2項演算
	class BinaryExpr: public Expr {
	public:
		const token_t get_operator() const { return token[0]; }

		std::unique_ptr<Expr> lhs, rhs;
	};

	// 代入
	class SubstitutionExpr : public Expr {
	public:
		std::unique_ptr<Expr> expr;
	};

	// 括弧
	class BracketsExpr : public Expr {
	public:
		void parse();

		std::unique_ptr<Expr> expr;
	};

	// 関数呼び出し
	class CallFuncExpr : public Expr {
	public:
		void parse();
		const token_t get_name() const { return token[0]; }

		std::unique_ptr<BracketsExpr> args;
	};

	// 変数定義
	// var hoge;
	// const fuga = hoge;
	class DefVariable : public Base {
	public:
		void parse();
		bool is_const() const { return ("const" == token[0]); }

		std::unique_ptr<Expr> init_expr;
	};

	// ブロック
	class Block : public Base {
	public:
		void parse();

		Block* parent = nullptr;
		std::vector<std::unique_ptr<Base>> sub;
	};

	// 関数定義
	class DefFuncBlock : public Block {
	public:
		void parse();
		const token_t get_name() const { return token[0]; }
	};

	// ifブロック
	class IfBlock : public Block {
	public:
		std::unique_ptr<Expr> cond_expr;
		std::vector<std::unique_ptr<Block>> else_block;
	};

	// loopブロック
	class LoopBlock : public Block {
	public:
		std::unique_ptr<Expr> init_expr, cond_expr, update_expr; // for(init;cond;update){}
	};
}

#endif
