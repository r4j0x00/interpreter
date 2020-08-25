#include <iostream>
#include <cassert>
#include <string>
#include "types.h"
#include "definitions.h"

Interpreter::Interpreter (Lexer lexer)
{
	this->lexer = lexer;
	this->current_token = this->lexer.get_next_token(); // sets the first token as current_token
}

void Interpreter::error()
{
	assert(0);
}

/* Assumes that the current_token is an integer or a left paranthesis
   Uses recursion to evaluate parenthesized expressions
   changes current_token to next token
   returns the integer value */
int Interpreter::factor()
{
	Token token = this->current_token;
	int value=0;
	if(token.get_type() == INTEGER)
	{
		this->eat(INTEGER);
		value = token.get_value();
	}
	else if(token.get_type() == LPAREN)
	{
		this->eat(LPAREN);
		value = this->eval();
		Token get_next_token();
		this->eat(RPAREN);
	}
	return value;
}

/* Pulls the current factor
   loops until the next operation is not multiplication or division
   returns the result after evaluation */
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

// Evaluate the current expression and return the result
int Interpreter::eval()
{
	int value = this->term();

	Token op = this->current_token;
	int type = op.get_type();
	while(type == PLUS || type == MINUS)
	{
		if(type == PLUS)
		{
			this->eat(PLUS);
			value += this->term();
		}
		else if(type == MINUS)
		{
			this->eat(MINUS);
			value -= this->term();
		}
		op = this->current_token;
		type = op.get_type();
	}
	if(type != Eof)
		this->error();
	return value;
}

/* Check if the provided type is equal to the type of current_token
   Set cuurent_token to next token */
void Interpreter::eat(int type)
{
	if (this->current_token.get_type() == type)
		this->current_token = this->lexer.get_next_token();
	else
		this->error();
}
