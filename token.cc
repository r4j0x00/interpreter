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
