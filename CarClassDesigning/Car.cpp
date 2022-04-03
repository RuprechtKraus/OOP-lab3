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
	switch (gear)
	{
	case Gear::Reverse:
		return SetReverseGear();
	case Gear::Neutral:
		return SetNeutralGear();
	case Gear::First:
		return SetFirstGear();
	case Gear::Second:
		return SetSecondGear();
	case Gear::Third:
		return SetThirdGear();
	case Gear::Fourth:
		return SetFourthGear();
	case Gear::Fifth:
		return SetFifthGear();
	default:
		break;
	}

	return false;
}

bool Car::SetReverseGear()
{
	if (CanSetReverseGear())
	{
		m_gear = Gear::Reverse;
		return true;
	}

	return false;
}

bool Car::CanSetReverseGear() const
{
	return m_speed && m_isEngineTurnedOn;
}

bool Car::SetNeutralGear()
{
	m_gear = Gear::Neutral;
	return true;
}

bool Car::SetFirstGear()
{
	if (CanSetFirstGear())
	{
		m_gear = Gear::First;
		return true;
	}

	return false;
}

bool Car::CanSetFirstGear() const
{
	const auto& speedRange{ gearSpeedRanges.at(Gear::First) };

	return ((m_gear != Gear::Reverse && 
		m_speed >= speedRange.min && 
		m_speed <= speedRange.max) || 
		(m_gear == Gear::Reverse && m_speed == 0)) && 
		m_isEngineTurnedOn;
}

bool Car::SetSecondGear()
{
	if (CanSetSecondGear())
	{
		m_gear = Gear::Second;
		return true;
	}

	return false;
}

bool Car::CanSetSecondGear() const
{
	const auto& speedRange{ gearSpeedRanges.at(Gear::Second) };

	return m_gear != Gear::Reverse && 
		m_speed >= speedRange.min && 
		m_speed <= speedRange.max &&
		m_isEngineTurnedOn;
}

bool Car::SetThirdGear()
{
	if (CanSetThirdGear())
	{
		m_gear = Gear::Third;
		return true;
	}

	return false;
}

bool Car::CanSetThirdGear() const
{
	const auto& speedRange{ gearSpeedRanges.at(Gear::Third) };

	return m_speed >= speedRange.min && 
		m_speed <= speedRange.max && 
		m_isEngineTurnedOn;
}

bool Car::SetFourthGear()
{
	if (CanSetFourthGear())
	{
		m_gear = Gear::Fourth;
		return true;
	}

	return false;
}

bool Car::CanSetFourthGear() const
{
	const auto& speedRange{ gearSpeedRanges.at(Gear::Fourth) };

	return m_speed >= speedRange.min && 
		m_speed <= speedRange.max && 
		m_isEngineTurnedOn;
}

bool Car::SetFifthGear()
{
	if (CanSetFifthGear())
	{
		m_gear = Gear::Fifth;
		return true;
	}

	return false;
}

bool Car::CanSetFifthGear() const
{
	const auto& speedRange{ gearSpeedRanges.at(Gear::Fifth) };

	return m_speed >= speedRange.min && 
		m_speed <= speedRange.max && 
		m_isEngineTurnedOn;
}

bool Car::SetSpeed(int speed)
{
	return false;
}