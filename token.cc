#include <cassert>
#include "types.h"
#include "definitions.h"

Token::Token() {
	this->type = None;
};

Token::Token(int type, int value)
{
	this->type = type; // defined in types.h
	this->value = value;
};

int Token::get_type()
{
	return this->type;
};

int Token::get_value()
{
	return this->value;
};
