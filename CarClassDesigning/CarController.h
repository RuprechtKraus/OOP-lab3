#pragma once
#include "Car.h"
#include <functional>

enum class HandlingStatus
{
	Fail,
	Success,
	UnknownCommand,
	Exit
};

class CarController
{
public:
	CarController(Car& car, std::istream& input, std::ostream& output);
	CarController& operator=(const CarController&) = delete;

	HandlingStatus HandleCommand();

private:
	using Handler = std::function<HandlingStatus(std::istream& args)>;
	using ActionMap = std::map<std::string, Handler>;

	HandlingStatus TurnOn(std::istream&) const;
	HandlingStatus TurnOff(std::istream&) const;
	HandlingStatus SetGear(std::istream&) const;
	HandlingStatus SetSpeed(std::istream&) const;
	HandlingStatus Info(std::istream&) const;
	void HandleEngineErorr(EngineError error) const;
	void HandleGearError(GearError error) const;
	void HandleSpeedError(SpeedError error) const;

	Car& m_car;
	std::istream& m_input;
	std::ostream& m_output;
	const ActionMap m_actionMap{
		{ "engineon", std::bind(&CarController::TurnOn, this, std::placeholders::_1) },
		{ "engineoff", std::bind(&CarController::TurnOff, this, std::placeholders::_1) },
		{ "setgear", std::bind(&CarController::SetGear, this, std::placeholders::_1) },
		{ "setspeed", std::bind(&CarController::SetSpeed, this, std::placeholders::_1) },
		{ "info", std::bind(&CarController::Info, this, std::placeholders::_1) },
		{ "exit", [](std::istream&) { return HandlingStatus::Exit; } }
	};
};