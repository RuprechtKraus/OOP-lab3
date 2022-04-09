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

HandlingResult CarController::HandleCommand()
{
	std::string command{};
	m_input >> command;
	ToLowerString(command);

	auto it = m_actionMap.find(command);
	if (it != m_actionMap.cend())
	{
		return it->second(m_input);
	}

	return HandlingResult::UnknownCommand;
}

HandlingResult CarController::TurnOn(std::istream&)
{
	if (!m_car.TurnOnEngine())
	{
		return HandlingResult::Fail;
	}

	return HandlingResult::Success;
}

HandlingResult CarController::TurnOff(std::istream&)
{
	if (!m_car.TurnOffEngine())
	{
		return HandlingResult::Fail;
	}

	return HandlingResult::Success;
}

HandlingResult CarController::SetGear(std::istream& args)
{
	int gear{};
	args >> gear;

	if (gear >= -1 && gear <= 5)
	{
		if (!m_car.SetGear(static_cast<Gear>(gear)))
		{
			m_output << "Unable to set gear"
					  << std::endl;
			return HandlingResult::Fail;
		}
	}
	else
	{
		m_output << "Wrong gear"
				  << std::endl;
		return HandlingResult::Fail;
	}

	return HandlingResult::Success;
}

HandlingResult CarController::SetSpeed(std::istream& args)
{
	int speed{};
	args >> speed;

	try
	{
		if (!m_car.SetSpeed(speed))
		{
			m_output << "Unable to set speed"
					  << std::endl;
			return HandlingResult::Fail;
		}
	}
	catch (const std::invalid_argument& e)
	{
		m_output << "Error: " << e.what() << std::endl;
		return HandlingResult::Fail;
	}

	return HandlingResult::Success;
}

HandlingResult CarController::Info(std::istream&)
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
		m_output << "Error: " << e.what() << std::endl;
		return HandlingResult::Fail;
	}

	return HandlingResult::Success;
}

void ToLowerString(std::string& str)
{
	std::transform(str.cbegin(), str.cend(), str.begin(), [](char c) { return tolower(c); });
}