#include "Car.h"
#include "CarController.h"
#include <algorithm>
#include <iostream>

int main() // TODO: Покрыть тестами код взаимодействия с пользователем CarController
{
	std::cout << "List of available commands:"
			  << "\nInfo"
			  << "\nEngineOn"
			  << "\nEngineOff"
			  << "\nSetGear <value from -1 to 5>"
			  << "\nSetSpeed <integer value>"
			  << "\nExit\n"
			  << std::endl;

	Car car;
	CarController carController(car, std::cin, std::cout);
	HandlingResult handlingResult{ HandlingResult::Success };

	while (handlingResult != HandlingResult::Exit)
	{
		std::cout << "> ";
		handlingResult = carController.HandleCommand();

		if (handlingResult == HandlingResult::UnknownCommand)
		{
			std::cout << "Unknown command" << std::endl;
		}
	}
}