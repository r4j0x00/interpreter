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
		Interpreter *interpreter = new Interpreter(code);
		std::cout << interpreter->eval() << '\n';
		code.clear();
		delete interpreter;
	}
	return 0;
}
