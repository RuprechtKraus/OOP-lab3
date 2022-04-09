#include "Car.h"
#include <stdexcept>

bool Car::IsTurnedOn() const
{
	return m_isEngineTurnedOn;
}

int Car::GetSpeed() const
{
	return m_speed;
}

Gear Car::GetGear() const
{
	return m_gear;
}

Direction Car::GetDirection() const
{
	return m_direction;
}

EngineError Car::TurnOnEngine()
{
	m_isEngineTurnedOn = true;
	return EngineError::NoError;
}

EngineError Car::TurnOffEngine()
{
	EngineError error{ CanTurnOffEngine() };

	if (error == EngineError::NoError)
	{
		m_isEngineTurnedOn = false;
	}

	return error;
}

EngineError Car::CanTurnOffEngine() const
{
	if (m_speed != 0)
	{
		return EngineError::CarIsMoving;
	}

	if (m_gear != Gear::Neutral)
	{
		return EngineError::GearIsNotNeutral;
	}

	return EngineError::NoError;
}

GearError Car::SetGear(Gear gear)
{
	GearError error{ CanSetGear(gear) };

	if (error == GearError::NoError)
	{
		m_gear = gear;
	}

	return error;
}

GearError Car::CanSetGear(Gear gear) const
{
	switch (gear)
	{
	case Gear::Reverse:
		return CanSetReverseGear();
	case Gear::Neutral:
		return GearError::NoError;
	case Gear::First:
	case Gear::Second:
	case Gear::Third:
	case Gear::Fourth:
	case Gear::Fifth:
		return CanSetForwardGear(gear);
	default:
		throw std::invalid_argument("Unexpected gear");
	}
}

GearError Car::CanSetReverseGear() const
{
	if (!m_isEngineTurnedOn)
	{
		return GearError::EngineIsOff;
	}

	if (m_direction != Direction::Backward && m_speed != 0)
	{
		return GearError::WrongDirection;
	}

	return GearError::NoError;
}

GearError Car::CanSetForwardGear(Gear gear) const
{
	const auto& speedRange{ gearSpeedRanges.at(gear) };

	if (!m_isEngineTurnedOn)
	{
		return GearError::EngineIsOff;
	}

	if (m_direction == Direction::Backward && m_speed != 0)
	{
		return GearError::WrongDirection;
	}

	if (m_speed < speedRange.min || m_speed > speedRange.max)
	{
		return GearError::WrongSpeed;
	}

	return GearError::NoError;
}

SpeedError Car::SetSpeed(int speed)
{
	if (speed < 0)
	{
		throw std::invalid_argument("Negative speed");
	}

	SpeedError error{ CanSetSpeed(speed) };

	if (error == SpeedError::NoError)
	{
		m_speed = speed;
		ChangeDirection();
		return error;
	}

	return error;
}

SpeedError Car::CanSetSpeed(int speed) const
{
	if (!m_isEngineTurnedOn)
	{
		return SpeedError::EngineIsOff;
	}

	if (m_gear == Gear::Neutral && speed > m_speed)
	{
		return SpeedError::AccelerateInNeutralGear;
	}

	const auto& speedRange{ gearSpeedRanges.at(m_gear) };

	if (speed < speedRange.min || speed > speedRange.max)
	{
		return SpeedError::WrongSpeed;
	}

	return SpeedError::NoError;
}

void Car::ChangeDirection()
{
	if (m_speed == 0)
	{
		m_direction = Direction::None;
		return;
	}

	if (m_speed != 0 && m_gear == Gear::Reverse)
	{
		m_direction = Direction::Backward;
		return;
	}

	if (m_speed != 0 && m_gear > Gear::Neutral)
	{
		m_direction = Direction::Forward;
		return;
	}
}