#include "CarController.h"
#include <algorithm>
#include <iostream>

void ToLowerString(std::string& str);

CarController::CarController(Car& car, std::istream& input, std::ostream& output)
	: m_car(car)
	, m_input(input)
	, m_output(output)
{
}

bool CarController::HandleCommand()
{
	std::string command{};
	m_input >> command;
	ToLowerString(command);

	auto it = m_actionMap.find(command);
	if (it != m_actionMap.cend())
	{
		it->second(m_input);
		return true;
	}

	return false;
}

void CarController::TurnOn(std::istream&)
{
	m_car.TurnOnEngine();
}

void CarController::TurnOff(std::istream&)
{
	m_car.TurnOffEngine();
}

void CarController::SetGear(std::istream& args)
{
	int gear{};
	args >> gear;

	if (gear >= -1 && gear <= 5)
	{
		if (!m_car.SetGear(static_cast<Gear>(gear)))
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

void CarController::SetSpeed(std::istream& args)
{
	int speed{};
	args >> speed;

	try
	{
		if (!m_car.SetSpeed(speed))
		{
			std::cout << "Unable to set speed"
					  << std::endl;
		}
	}
	catch (const std::invalid_argument& e)
	{
		std::cout << "Error: " << e.what() << std::endl;
	}
}

void CarController::Info(std::istream&)
{
	try
	{
		m_output << "Engine: " << (m_car.IsTurnedOn() ? "Engine is on" : "Engine is off");
		m_output << "\nGear: " << GearToString(m_car.GetGear());
		m_output << "\nDirection: " << DirectionToString(m_car.GetDirection());
		m_output << "\nSpeed: " << m_car.GetSpeed() << " km/h"
				 << std::endl;
	}
	catch (const std::invalid_argument& e)
	{
		std::cout << "Error: " << e.what() << std::endl;
	}
}

void ToLowerString(std::string& str)
{
	std::transform(str.cbegin(), str.cend(), str.begin(), [](char c) { return tolower(c); });
}