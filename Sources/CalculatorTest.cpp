#include "Calculator.h"
#include <iostream>

int main()
{
	Calculator calc;

	try
	{
		calc.Run();
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
	catch (...)
	{
		std::cout << "Unknown exception error" << std::endl;
	}

	return 0;
}