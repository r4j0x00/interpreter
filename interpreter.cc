#include <iostream>
#include <cassert>
#include "types.h"
#include "definitions.h"

Interpreter::Interpreter (std::string _code)
{
	pos = 0;
	code = _code;
}

void Interpreter::error()
{
	assert(0);
}

Token Interpreter::get_next_token ()
{
	Token token;
	int size = code.length();
	if (pos > size - 1)
		return Token(Eof, None);

	char cur = code[pos++];
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

	error();
	ret:
		return token;
}

int Interpreter::eval()
{
	current_token = get_next_token();
	Token left = current_token;
	eat(INTEGER);

	Token op = current_token;
	eat(PLUS);

	Token right = current_token;
	eat(INTEGER);

	return left.get_value() + right.get_value();
}


void Interpreter::eat(int type)
{
	if (current_token.get_type() == type)
		current_token = get_next_token();
	else
		error();
}
