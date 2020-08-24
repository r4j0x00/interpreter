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
		std::cin >> code;
		Interpreter interpreter(code);
		std::cout << interpreter.eval() << '\n';
	}
	return 0;
}
