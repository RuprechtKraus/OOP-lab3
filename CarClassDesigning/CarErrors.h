#pragma once

enum class EngineError
{
	CarIsMoving,
	GearIsNotNeutral,
	NoError
};

enum class GearError
{
	EngineIsOff,
	WrongSpeed,
	WrongDirection,
	NoError
};

enum class SpeedError
{
	EngineIsOff,
	AccelerateInNeutralGear,
	WrongSpeed,
	NoError
};