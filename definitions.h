#pragma once
#include <iostream>
#include "types.h"
#define is_whitespace(c) (c == ' ' || c == '\t')
#define is_digit(d) (d >= '0' && d <= '9')
#define is_valid_operation(op) (op == PLUS || op == MINUS || op == MUL || op == DIV || op == LPAREN || op == RPAREN)

class Token
{
	public:
		Token();
		Token(int type, int value);
		int get_type();
		int get_value();
	private:
		int type;
		int value;
};

class Lexer
{
	public:
		Lexer();
		Lexer(const std::string &code);
		Token get_next_token();
	private:
		int pos;
		void skip_whitespace();
		std::string code;
		char current_char;
		void error();
		int size;
		void advance();
		int intvalue();
};

class Interpreter
{
	public:
		Interpreter(Lexer lexer);
		int eval();
	private:
		Lexer lexer;
		Token current_token;
		void error();
		void eat(int type);
		int factor();
		int term();
};
