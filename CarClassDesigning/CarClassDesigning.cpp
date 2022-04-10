#include "Car.h"
#include "CarController.h"
#include <algorithm>
#include <iostream>

int main()
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
	HandlingStatus handlingResult{ HandlingStatus::Success };

	while (handlingResult != HandlingStatus::Exit)
	{
		std::cout << "> ";
		handlingResult = carController.HandleCommand();

		if (handlingResult == HandlingStatus::UnknownCommand)
		{
			std::cout << "Unknown command" << std::endl;	
		}

		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}
}