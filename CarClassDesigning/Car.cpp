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

bool Car::TurnOnEngine()
{
	m_isEngineTurnedOn = true;
	return true;
}

bool Car::TurnOffEngine()
{
	if (!m_isEngineTurnedOn)
	{
		return true;
	}

	if (CanTurnOffEngine())
	{
		m_isEngineTurnedOn = false;
		return true;
	}

	return false;
}

bool Car::CanTurnOffEngine() const
{
	return m_gear == Gear::Neutral && m_speed == 0;
}

bool Car::SetGear(Gear gear)
{
	if (CanSetGear(gear))
	{
		m_gear = gear;
		return true;
	}

	return false;
}

bool Car::CanSetGear(Gear gear) const
{
	const auto& speedRange{ gearSpeedRanges.at(gear) };

	switch (gear)
	{
	case Gear::Reverse:
		return m_speed == 0 && m_isEngineTurnedOn;
	case Gear::Neutral:
		return true;
	case Gear::First:
		return ((m_gear != Gear::Reverse && 
			m_speed >= speedRange.min && 
			m_speed <= speedRange.max && 
			m_direction != Direction::Backward) || 
			(m_gear == Gear::Reverse && m_speed == 0)) && 
			m_isEngineTurnedOn;
	case Gear::Second:
		return m_gear != Gear::Reverse && 
			m_speed >= speedRange.min && 
			m_speed <= speedRange.max && 
			m_direction != Direction::Backward && 
			m_isEngineTurnedOn;
	case Gear::Third:
	case Gear::Fourth:
	case Gear::Fifth:
		return m_speed >= speedRange.min && 
			m_speed <= speedRange.max && 
			m_direction != Direction::Backward && 
			m_isEngineTurnedOn;
	default:
		return false;
	}
}

bool Car::SetSpeed(int speed)
{
	if (speed < 0)
	{
		throw std::invalid_argument("Negative speed");
	}

	if (CanSetSpeed(speed))
	{
		m_speed = speed;
		ChangeDirection();
		return true;
	}

	return false;
}

bool Car::CanSetSpeed(int speed) const
{
	if (m_gear == Gear::Neutral)
	{
		return speed < m_speed;
	}

	const auto& speedRange{ gearSpeedRanges.at(m_gear) };

	if (speed >= speedRange.min && speed <= speedRange.max)
	{
		return true;
	}

	return false;
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