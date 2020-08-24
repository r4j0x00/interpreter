#include <iostream>
#include <cassert>
#include <string>
#include "types.h"
#include "definitions.h"

Interpreter::Interpreter (std::string code)
{
	this->pos = 0;
	this->code = code;
	this->size = code.length();
	if (!size)
		this->error();
	this->current_char = code[0];
}

void Interpreter::error()
{
	assert(0);
}

void Interpreter::advance()
{
	if(++this->pos >= this->size)
		this->current_char = 0;
	else
		this->current_char = this->code[pos];
}

void Interpreter::skip_whitespace()
{
	while (is_whitespace(this->current_char))
		this->advance();
}

int Interpreter::intvalue()
{
	std::string res;
	while(is_digit(this->current_char))
	{
		res += this->current_char;
		this->advance();
	}
	if(!res.length())
		this->error();
	int value = std::stoi(res);
	res.clear();
	return value;
}

Token Interpreter::get_next_token ()
{
	Token token;

	if (this->pos > this->size - 1)
		return Token(Eof, None);

	if(is_whitespace(this->current_char))
		this->skip_whitespace();

	if(is_digit(this->current_char))
	{
		token = Token(INTEGER, this->intvalue()); // calls this->advance() at the end
		goto ret;
	}

	if(this->current_char == '+')
	{
		token = Token(PLUS, this->current_char);
		this->advance();
		goto ret;
	}

	if(this->current_char == '-')
	{
		token = Token(MINUS, this->current_char);
		this->advance();
		goto ret;
	}

	if(this->current_char == '*')
	{
		token = Token(MUL, this->current_char);
		this->advance();
		goto ret;
	}

	if(this->current_char == '/')
	{
		token = Token(DIV, this->current_char);
		this->advance();
		goto ret;
	}

	this->error();
	ret:
		return token;
}

int Interpreter::term()
{
	Token token = this->current_token;
	this->eat(INTEGER);
	return token.get_value();
}

int Interpreter::eval()
{
	this->current_token = this->get_next_token();
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
		else if(type == MUL)
		{
			eat(MUL);
			value *= this->term();
		}
		else if(type == DIV)
		{
			eat(DIV);
			value /= this->term();
		}
		op = this->current_token;
		type = op.get_type();
	}
	return value;
}


void Interpreter::eat(int type)
{
	if (this->current_token.get_type() == type)
		this->current_token = get_next_token();
	else
		this->error();
}
