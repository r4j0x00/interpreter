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

	this->error();
	ret:
		return token;
}

int Interpreter::eval()
{
	this->current_token = this->get_next_token();
	Token left = this->current_token;
	eat(INTEGER);

	Token op = this->current_token;
	int type = op.get_type();
	if(type == PLUS)
		eat(PLUS);
	else if(type == MINUS)
		eat(MINUS);

	Token right = this->current_token;
	eat(INTEGER);
	int value;

	if(type == PLUS)
		return left.get_value() + right.get_value();
	return left.get_value() - right.get_value();
}


void Interpreter::eat(int type)
{
	if (this->current_token.get_type() == type)
		this->current_token = get_next_token();
	else
		this->error();
}
