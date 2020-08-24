#include <iostream>
#include <cassert>
#include <string>
#include "types.h"
#include "definitions.h"

Interpreter::Interpreter (Lexer lexer)
{
	this->lexer = lexer;
	this->current_token = this->lexer.get_next_token();
}

void Interpreter::error()
{
	assert(0);
}

int Interpreter::factor()
{
	Token token = this->current_token;
	this->eat(INTEGER);
	return token.get_value();
}

int Interpreter::term()
{
	int res = this->factor();
	Token token = this->current_token;
	int type = token.get_type();
	while(type == MUL || type == DIV)
	{
		if (type == MUL)
		{
			this->eat(MUL);
			res *= this->factor();
		}

		if (type == DIV)
		{
			this->eat(DIV);
			res /= this->factor();
		}
		token = this->current_token;
		type = token.get_type();
	}
	return res;
}

int Interpreter::eval()
{
	int value = this->term();

	Token op = this->current_token;
	int type = op.get_type();
	while(is_valid_operation(type))
	{
		if(type == PLUS)
		{
			eat(PLUS);
			value += this->term();
		}
		else if(type == MINUS)
		{
			eat(MINUS);
			value -= this->term();
		}
		op = this->current_token;
		type = op.get_type();
	}
	return value;
}


void Interpreter::eat(int type)
{
	if (this->current_token.get_type() == type)
		this->current_token = this->lexer.get_next_token();
	else
		this->error();
}
