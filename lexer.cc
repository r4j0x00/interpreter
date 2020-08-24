#include <iostream>
#include <cassert>
#include <string>
#include "types.h"
#include "definitions.h"


Lexer::Lexer() { }

/* Takes the expression in the form of a string
   Does lexical analysis and generates a sequence of tokens */
Lexer::Lexer (std::string code)
{
	this->pos = 0;
	this->code = code;
	this->size = code.length();
	if (!size)
		this->error();
	this->current_char = code[0];
}

void Lexer::error()
{
	assert(0);
}

/* Checks if the next position is valid
   if so, then sets the current char to the next position
   otherwise, the current_char is set to null */
void Lexer::advance()
{
	if(++this->pos >= this->size)
		this->current_char = 0;
	else
		this->current_char = this->code[pos];
}

// advances until a non-whitespace character is found
void Lexer::skip_whitespace()
{
	while (is_whitespace(this->current_char))
		this->advance();
}

/* advances until a non-digit value is found
   the integer value is returned */
int Lexer::intvalue()
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

/* Checks if the next token is available
   if not Eof is returned
   It's checked if the new token is valid and returned
   otherwise errors out */
Token Lexer::get_next_token ()
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
