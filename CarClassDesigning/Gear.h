#pragma once
#include <string>
#include <stdexcept>

enum class Gear
{
	Reverse = -1,
	Neutral,
	First,
	Second,
	Third,
	Fourth,
	Fifth
};

static std::string GearToString(Gear gear)
{
	switch (gear)
	{
	case Gear::Reverse:
		return "Reverse";
	case Gear::Neutral:
		return "Neutral";
	case Gear::First:
		return "First";
	case Gear::Second:
		return "Second";
	case Gear::Third:
		return "Third";
	case Gear::Fourth:
		return "Fourth";
	case Gear::Fifth:
		return "Fifth";
	default:
		throw std::invalid_argument("Unexpected gear");
	}
}