#pragma once
#include <iostream>
#define is_whitespace(c) (c == ' ' || c == '\t')
#define is_digit(d) (d >= '0' && d <= '9')
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

class Interpreter
{	public:
		Interpreter(std::string code);
		int eval();
	private:
		int pos;
		void skip_whitespace();
		std::string code;
		Token current_token;
		char current_char;
		Token get_next_token();
		void error();
		void eat(int type);
		int size;
		void advance();
		int intvalue();
};
