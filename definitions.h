#pragma once
#include <iostream>

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
		std::string code;
		Token current_token;
		Token get_next_token();
		void error();
		void eat(int type);	

};
