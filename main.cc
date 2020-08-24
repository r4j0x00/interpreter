#include <iostream>
#include <vector>
#include <cassert>
#include "definitions.h"
int main(void)
{
	while(1)
	{
		std::cout << ">>> ";
		std::string code;
		std::getline(std::cin, code);
		if(code.length())
		{
			Interpreter *interpreter = new Interpreter(code);
			std::cout << interpreter->eval() << '\n';
			delete interpreter;
		}
		code.clear();
	}
	return 0;
}
