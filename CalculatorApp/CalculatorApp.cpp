#include "Calculator.h"
#include "CalculatorController.h"
#include <iostream>
#include <iomanip>

int main()
{
	Calculator calculator;
	CalculatorController controller(calculator, std::cin, std::cout);

	controller.ShowHelp();
	controller.BeginControl();
}