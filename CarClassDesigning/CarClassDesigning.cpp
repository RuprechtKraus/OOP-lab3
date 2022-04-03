#include "Car.h"
#include <algorithm>
#include <iostream>

std::string INFO_COMMAND = "info";
std::string ENGINE_ON_COMMAND = "engineon";
std::string ENGINE_OFF_COMMAND = "engineoff";
std::string SET_GEAR_COMMAND = "setgear";
std::string SET_SPEED_COMMAND = "setspeed";
std::string EXIT_COMMAND = "exit";

void HandleCommand(Car& car, const std::string& command);
void PrintCarInfo(const Car& car);
void SetCarGear(Car& car, int gear);
void SetCarSpeed(Car& car, int speed);
void ToLowerString(std::string& str);
void HandleEngineOffCommand(Car& car);
void HandleSetGearCommand(Car& car);
void HandleSetSpeedCommand(Car& car);

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
	std::string command{};

	while (true)
	{
		std::cout << "Enter a command: ";
		std::cin >> command;
		ToLowerString(command);

		if (command == EXIT_COMMAND)
		{
			break;
		}

		HandleCommand(car, command);
	}
}

void HandleCommand(Car& car, const std::string& command)
{
	if (command == INFO_COMMAND)
	{
		PrintCarInfo(car);
		return;
	}

	if (command == ENGINE_ON_COMMAND)
	{
		car.TurnOnEngine();
		return;
	}

	if (command == ENGINE_OFF_COMMAND)
	{
		HandleEngineOffCommand(car);
		return;
	}

	if (command == SET_GEAR_COMMAND)
	{
		HandleSetGearCommand(car);
		return;
	}

	if (command == SET_SPEED_COMMAND)
	{
		HandleSetSpeedCommand(car);
		return;
	}

	std::cout << "Unknown command\n"
			  << std::endl;
}

void HandleEngineOffCommand(Car& car)
{
	if (!car.TurnOffEngine())
	{
		std::cout << "Unable to turn off engine\n"
				  << std::endl;
	}
}

void HandleSetGearCommand(Car& car)
{
	int gear{};
	std::cin >> gear;
	SetCarGear(car, gear);
}

void HandleSetSpeedCommand(Car& car)
{
	int speed{};
	std::cin >> speed;
	SetCarSpeed(car, speed);
}

void PrintCarInfo(const Car& car)
{
	try
	{
		std::cout << "Engine: " << (car.IsTurnedOn() ? "Engine is on" : "Engine is off");
		std::cout << "\nGear: " << GearToString(car.GetGear());
		std::cout << "\nDirection: " << DirectionToString(car.GetDirection());
		std::cout << "\nSpeed: " << car.GetSpeed() << " km/h"
				  << std::endl;
	}
	catch (const std::invalid_argument& e)
	{
		std::cout << "Error: " << e.what() << std::endl;
	}
}

void SetCarGear(Car& car, int gear)
{
	if (gear >= -1 && gear <= 5)
	{
		if (!car.SetGear(static_cast<Gear>(gear)))
		{
			std::cout << "Unable to set gear\n"
					  << std::endl;
		}
	}
	else
	{
		std::cout << "Wrong gear\n"
				  << std::endl;
	}
}

void SetCarSpeed(Car& car, int speed)
{
	if (speed >= 0)
	{
		if (!car.SetSpeed(speed))
		{
			std::cout << "Unable to set speed\n"
					  << std::endl;
		}
	}
	else
	{
		std::cout << "Negative speed\n"
				  << std::endl;
	}
}

void ToLowerString(std::string& str)
{
	std::transform(str.cbegin(), str.cend(), str.begin(), [](char c) { return tolower(c); });
}