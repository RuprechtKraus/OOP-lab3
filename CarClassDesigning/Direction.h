#pragma once
#include <string>
#include <stdexcept>

enum class Direction
{
	None,
	Backward,
	Forward
};

static std::string DirectionToString(Direction direction)
{
	switch (direction)
	{
	case Direction::None:
		return "None";
	case Direction::Backward:
		return "Backward";
	case Direction::Forward:
		return "Forward";
	default:
		throw std::invalid_argument("Unexpected direction");
	}
}