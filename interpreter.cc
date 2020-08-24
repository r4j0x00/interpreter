#include <iostream>
#include <cassert>
#include "types.h"
#include "definitions.h"

Interpreter::Interpreter (std::string code)
{
	this->pos = 0;
	this->code = code;
}

void Interpreter::error()
{
	assert(0);
}

Token Interpreter::get_next_token ()
{
	Token token;
	int size = this->code.length();
	if (this->pos > size - 1)
		return Token(Eof, None);

	char cur = this->code[this->pos++];
	if(cur >= '0' && cur <= '9')
	{
		token = Token(INTEGER, cur-48);
		goto ret;
	}

	if(cur == '+')
	{
		token = Token(PLUS, cur);
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
