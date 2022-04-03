#pragma once
#include <string>
#include <stdexcept>

enum class Direction
{
	Backward,
	Forward,
	None
};

static std::string DirectionToString(Direction direction)
{
	switch (direction)
	{
	case Direction::Backward:
		return "Backward";
	case Direction::Forward:
		return "Forward";
	case Direction::None:
		return "None";
	default:
		throw std::invalid_argument("Unexpected direction");
	}
}