#pragma once
#include "Car.h"
#include <functional>

enum class HandlingResult
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

	HandlingResult HandleCommand();

private:
	using Handler = std::function<HandlingResult(std::istream& args)>;
	using ActionMap = std::map<std::string, Handler>;

	HandlingResult TurnOn(std::istream&);
	HandlingResult TurnOff(std::istream&);
	HandlingResult SetGear(std::istream&);
	HandlingResult SetSpeed(std::istream&);
	HandlingResult Info(std::istream&);

	Car& m_car;
	std::istream& m_input;
	std::ostream& m_output;
	const ActionMap m_actionMap{
		{ "engineon", std::bind(&CarController::TurnOn, this, std::placeholders::_1) },
		{ "engineoff", std::bind(&CarController::TurnOff, this, std::placeholders::_1) },
		{ "setgear", std::bind(&CarController::SetGear, this, std::placeholders::_1) },
		{ "setspeed", std::bind(&CarController::SetSpeed, this, std::placeholders::_1) },
		{ "info", std::bind(&CarController::Info, this, std::placeholders::_1) },
		{ "exit", [](std::istream&) { return HandlingResult::Exit; } }
	};
};