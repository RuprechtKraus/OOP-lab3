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

HandlingStatus CarController::HandleCommand()
{
	std::string command{};
	m_input >> command;
	ToLowerString(command);

	auto it = m_actionMap.find(command);
	if (it != m_actionMap.cend())
	{
		return it->second(m_input);
	}

	return HandlingStatus::UnknownCommand;
}

HandlingStatus CarController::TurnOn(std::istream&) const
{
	if (m_car.TurnOnEngine() == EngineError::NoError)
	{
		return HandlingStatus::Success;
	}

	return HandlingStatus::Fail;
}

HandlingStatus CarController::TurnOff(std::istream&) const
{
	EngineError error{ m_car.TurnOffEngine() };

	if (error != EngineError::NoError)
	{
		HandleEngineErorr(error);
		return HandlingStatus::Fail;
	}
	
	return HandlingStatus::Success;
}

void CarController::HandleEngineErorr(EngineError error) const
{
	switch (error)
	{
	case EngineError::CarIsMoving:
		m_output << "Cannot turn the engine off while moving" << std::endl;
		break;
	case EngineError::GearIsNotNeutral:
		m_output << "Cannot turn the engine off not in neutral gear" << std::endl;
		break;
	default:
		break;
	}
}

HandlingStatus CarController::SetGear(std::istream& args) const
{
	int gear{};
	args >> gear;

	if (gear >= -1 && gear <= 5)
	{
		GearError error{ m_car.SetGear(static_cast<Gear>(gear)) };

		if (error != GearError::NoError)
		{
			HandleGearError(error);
			return HandlingStatus::Fail;
		}
	}
	else
	{
		m_output << "Wrong gear"
				 << std::endl;
		return HandlingStatus::Fail;
	}

	return HandlingStatus::Success;
}

void CarController::HandleGearError(GearError error) const
{
	switch (error)
	{
	case GearError::EngineIsOff:
		m_output << "Unable to set gear: engine is off" << std::endl;
		break;
	case GearError::WrongSpeed:
		m_output << "Unable to set gear: wrong speed" << std::endl;
		break;
	case GearError::WrongDirection:
		m_output << "Unable to set gear: car is moving in the wrong direction" << std::endl;
		break;
	default:
		return;
	}
}

HandlingStatus CarController::SetSpeed(std::istream& args) const
{
	int speed{};
	args >> speed;

	try
	{
		SpeedError error{ m_car.SetSpeed(speed) };

		if (error != SpeedError::NoError)
		{
			HandleSpeedError(error);
			return HandlingStatus::Fail;
		}
	}
	catch (const std::invalid_argument& e)
	{
		m_output << "Error: " << e.what() << std::endl;
		return HandlingStatus::Fail;
	}

	return HandlingStatus::Success;
}

void CarController::HandleSpeedError(SpeedError error) const
{
	switch (error)
	{
	case SpeedError::EngineIsOff:
		m_output << "Unable to set speed: engine is off" << std::endl;
		break;
	case SpeedError::AccelerateInNeutralGear:
		m_output << "Unable to set speed: acceleration in neutral speed is not allowed" << std::endl;
		break;
	case SpeedError::WrongSpeed:
		m_output << "Unable to set speed: current gear doesn't allow this speed" << std::endl;
		break;
	default:
		break;
	}
}

HandlingStatus CarController::Info(std::istream&) const
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
		return HandlingStatus::Fail;
	}

	return HandlingStatus::Success;
}

void ToLowerString(std::string& str)
{
	std::transform(str.cbegin(), str.cend(), str.begin(), [](char c) { return tolower(c); });
}