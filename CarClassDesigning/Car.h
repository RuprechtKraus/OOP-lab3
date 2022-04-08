#pragma once
#include "Gear.h"
#include "Direction.h"
#include <map>

class Car
{
public:
	bool IsTurnedOn() const;
	int GetSpeed() const;
	Gear GetGear() const;
	Direction GetDirection() const;
	bool TurnOnEngine();
	bool TurnOffEngine();
	bool SetGear(Gear gear);
	bool SetSpeed(int speed);

private:
	struct SpeedRange
	{
		int min;
		int max;
	};

	bool CanTurnOffEngine() const;
	bool CanSetSpeed(int speed) const;
	bool CanSetGear(Gear gear) const;
	void ChangeDirection();

	const std::map<Gear, SpeedRange> gearSpeedRanges = {
		{ Gear::Reverse, SpeedRange{ 0, 20 } },
		{ Gear::Neutral, SpeedRange{ 0, std::numeric_limits<int>::max() } },
		{ Gear::First, SpeedRange{ 0, 30 } },
		{ Gear::Second, SpeedRange{ 20, 50 } },
		{ Gear::Third, SpeedRange{ 30, 60 } },
		{ Gear::Fourth, SpeedRange{ 40, 90 } },
		{ Gear::Fifth, SpeedRange{ 50, 150 } }
	};

	int m_speed{ 0 };
	Direction m_direction{ Direction::None };
	Gear m_gear{ Gear::Neutral };
	bool m_isEngineTurnedOn{ false };
};