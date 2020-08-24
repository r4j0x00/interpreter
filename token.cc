#include <cassert>
#include "types.h"
#include "definitions.h"

Token::Token() {
	type = None;
};

Token::Token(int _type, int _value)
{
	type = _type;
	value = _value;
};

int Token::get_type()
{
	return type;
};

int Token::get_value()
{
	return value;
};
