#pragma once
#include "Car.h"
#include <functional>

class CarController
{
public:
	CarController(Car& car, std::istream& input, std::ostream& output);
	CarController& operator=(const CarController&) = delete;

	bool HandleCommand();

private:
	using Handler = std::function<void(std::istream& args)>;
	using ActionMap = std::map<std::string, Handler>;

	void TurnOn(std::istream&);
	void TurnOff(std::istream&);
	void SetGear(std::istream&);
	void SetSpeed(std::istream&);
	void Info(std::istream&);

	Car& m_car;
	std::istream& m_input;
	std::ostream& m_output;
	const ActionMap m_actionMap{
		{ "engineon", std::bind(&CarController::TurnOn, this, std::placeholders::_1) },
		{ "engineoff", std::bind(&CarController::TurnOff, this, std::placeholders::_1) },
		{ "setgear", std::bind(&CarController::SetGear, this, std::placeholders::_1) },
		{ "setspeed", std::bind(&CarController::SetSpeed, this, std::placeholders::_1) },
		{ "info", std::bind(&CarController::Info, this, std::placeholders::_1) }
	};
};