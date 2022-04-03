#include "Car.h"

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
	return false;
}

bool Car::SetGear(Gear gear)
{
	return false;
}

bool Car::SetSpeed(int speed)
{
	return false;
}