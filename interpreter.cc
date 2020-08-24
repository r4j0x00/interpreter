#include <iostream>
#include <cassert>
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

Token Interpreter::get_next_token ()
{
	Token token;
	if (this->pos > this->size - 1)
		return Token(Eof, None);

	this->current_char = this->code[this->pos++];
	if(this->current_char >= '0' && this->current_char <= '9')
	{
		token = Token(INTEGER, this->current_char-48);
		goto ret;
	}

	if(this->current_char == '+')
	{
		token = Token(PLUS, this->current_char);
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
	eat(PLUS);

	Token right = this->current_token;
	eat(INTEGER);

	return left.get_value() + right.get_value();
}


void Interpreter::eat(int type)
{
	if (this->current_token.get_type() == type)
		this->current_token = get_next_token();
	else
		this->error();
}
