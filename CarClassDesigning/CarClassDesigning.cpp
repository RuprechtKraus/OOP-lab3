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
bool IsNumber(const std::string& str);

int main() //TODO: Покрыть тестами код взаимодействия с пользователем CarController
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
		while (std::cin.get() != '\n') { } // Отбрасываем лишние символы
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

	std::cout << "Unknown command"
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
	std::string gear{};
	std::cin >> gear;
	if (IsNumber(gear))
	{
		SetCarGear(car, std::atoi(gear.c_str()));
	}
	else
	{
		std::cout << "Invalid gear value" << std::endl;
	}
}

void HandleSetSpeedCommand(Car& car)
{
	std::string speed{};
	std::cin >> speed;
	if (IsNumber(speed))
	{
		SetCarSpeed(car, std::atoi(speed.c_str()));
	}
	else
	{
		std::cout << "Invalid speed value" << std::endl;
	}
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
			std::cout << "Unable to set gear"
					  << std::endl;
		}
	}
	else
	{
		std::cout << "Wrong gear"
				  << std::endl;
	}
}

void SetCarSpeed(Car& car, int speed)
{
	if (speed >= 0)
	{
		if (!car.SetSpeed(speed))
		{
			std::cout << "Unable to set speed"
					  << std::endl;
		}
	}
	else
	{
		std::cout << "Negative speed"
				  << std::endl;
	}
}

bool IsNumber(const std::string& str)
{
	return (str[0] == '-' || std::isdigit(str[0])) && 
		!str.empty() && std::find_if(str.cbegin() + 1, str.cend(), [](unsigned char c) {
		return !std::isdigit(c);
	}) == str.cend();
}

void ToLowerString(std::string& str)
{
	std::transform(str.cbegin(), str.cend(), str.begin(), [](char c) { return tolower(c); });
}