#include "pch.h"
#include "CppUnitTest.h"
#include <sstream>
#include <optional>
#include "../CarClassDesigning/Car.h"
#include "../CarClassDesigning/CarController.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

struct CarControllerDependencies
{
	Car car;
	std::stringstream input;
	std::stringstream output;
};

class CarTestController : public CarControllerDependencies
{
public:
	CarTestController()
		: m_carController(car, input, output){};

	void VerifyCommandHandling(const std::string& command, 
		HandlingStatus expectedHandlingStatus,
		const std::optional<Gear>& expectedGear, 
		const std::optional<int>& expectedSpeed,
		const std::optional<Direction>& expectedDirection,
		const std::string& expectedOutput)
	{
		input = std::stringstream();
		output = std::stringstream();
		input << command;

		Assert::IsTrue(m_carController.HandleCommand() == expectedHandlingStatus, L"Command handling failed");
		Assert::IsTrue(car.IsTurnedOn() == expectedGear.has_value(), L"Engine isn't on");
		Assert::IsTrue(car.IsTurnedOn() == expectedSpeed.has_value(), L"Engine isn't on");
		Assert::IsTrue(car.IsTurnedOn() == expectedDirection.has_value(), L"Engine isn't on");
		Assert::IsTrue(car.GetGear() == expectedGear.value_or(Gear::Neutral), L"Actual gear doesn't match expected gear");
		Assert::IsTrue(car.GetSpeed() == expectedSpeed.value_or(0), L"Actual speed doesn't match expected speed");
		Assert::IsTrue(car.GetDirection() == expectedDirection.value_or(Direction::None), L"Actual direction doesn't match expected direction");
		Assert::IsTrue(input.eof(), L"There is input left in stream");
		Assert::AreEqual(output.str(), expectedOutput, L"Actual output doesn't match expected output");
	}

private:
	CarController m_carController;
};

namespace CarTest
{
	TEST_CLASS(CarTest)
	{
	public:
		TEST_METHOD(TestTurnOnEngine)
		{
			Car car;
			car.TurnOnEngine();
			
			Assert::IsTrue(car.IsTurnedOn(), L"Engine isn't on");
			Assert::IsTrue(car.GetDirection() == Direction::None, L"Direction isn't None");
			Assert::IsTrue(car.GetGear() == Gear::Neutral, L"Car isn't at neutral gear");
			Assert::IsTrue(car.GetSpeed() == 0, L"Speed isn't 0");
		}

		TEST_METHOD(TestSetFirstGear)
		{
			Car car;
			car.TurnOnEngine();

			GearError gearError{ car.SetGear(Gear::First) };

			Assert::IsTrue(gearError == GearError::NoError);
			Assert::IsTrue(car.IsTurnedOn(), L"Engine isn't on");
			Assert::IsTrue(car.GetDirection() == Direction::None, L"Direction isn't None");
			Assert::IsTrue(car.GetGear() == Gear::First, L"Car isn't at first gear");
			Assert::IsTrue(car.GetSpeed() == 0, L"Speed isn't 0");
		}

		TEST_METHOD(TestSetReverseGear)
		{
			Car car;
			car.TurnOnEngine();

			GearError gearError{ car.SetGear(Gear::Reverse) };

			Assert::IsTrue(gearError == GearError::NoError, L"Gear wasn't successfully set");
			Assert::IsTrue(car.GetGear() == Gear::Reverse, L"Car isn't at Reverse gear");
		}

		TEST_METHOD(TestSetAllGearsInTurn)
		{
			Car car;
			car.TurnOnEngine();

			GearError gearError{ car.SetGear(Gear::First) };
			SpeedError speedError{ car.SetSpeed(30) };

			Assert::IsTrue(car.GetDirection() == Direction::Forward, L"Direction isn't forward");
			Assert::IsTrue(gearError == GearError::NoError, L"Gear wasn't successfully set");
			Assert::IsTrue(speedError == SpeedError::NoError, L"Speed wasn't successfully set");
			Assert::AreEqual(30, car.GetSpeed(), L"Speed isn't 30");

			gearError = car.SetGear(Gear::Second);
			speedError = car.SetSpeed(40);

			Assert::IsTrue(car.GetDirection() == Direction::Forward, L"Direction isn't forward");
			Assert::IsTrue(gearError == GearError::NoError, L"Gear wasn't successfully set");
			Assert::IsTrue(speedError == SpeedError::NoError, L"Speed wasn't successfully set");
			Assert::IsTrue(car.GetGear() == Gear::Second, L"Car isn't at second gear");
			Assert::AreEqual(40, car.GetSpeed(), L"Speed isn't 30");

			gearError = car.SetGear(Gear::Third);
			speedError = car.SetSpeed(50);

			Assert::IsTrue(car.GetDirection() == Direction::Forward, L"Direction isn't forward");
			Assert::IsTrue(gearError == GearError::NoError, L"Gear wasn't successfully set");
			Assert::IsTrue(speedError == SpeedError::NoError, L"Speed wasn't successfully set");
			Assert::IsTrue(car.GetGear() == Gear::Third, L"Car isn't at third gear");
			Assert::AreEqual(50, car.GetSpeed(), L"Speed isn't 50");

			gearError = car.SetGear(Gear::Fourth);
			speedError = car.SetSpeed(70);

			Assert::IsTrue(car.GetDirection() == Direction::Forward, L"Direction isn't forward");
			Assert::IsTrue(gearError == GearError::NoError, L"Gear wasn't successfully set");
			Assert::IsTrue(speedError == SpeedError::NoError, L"Speed wasn't successfully set");
			Assert::IsTrue(car.GetGear() == Gear::Fourth, L"Car isn't at fourth gear");
			Assert::AreEqual(70, car.GetSpeed(), L"Speed isn't 70");

			gearError = car.SetGear(Gear::Fifth);
			speedError = car.SetSpeed(150);

			Assert::IsTrue(car.GetDirection() == Direction::Forward, L"Direction isn't forward");
			Assert::IsTrue(gearError == GearError::NoError, L"Gear wasn't successfully set");
			Assert::IsTrue(speedError == SpeedError::NoError, L"Speed wasn't successfully set");
			Assert::IsTrue(car.GetGear() == Gear::Fifth, L"Car isn't at fifth gear");
			Assert::AreEqual(150, car.GetSpeed(), L"Speed isn't 150");
		}

		TEST_METHOD(TestSetGearFromSecondToFifth)
		{
			Car car;
			car.TurnOnEngine();

			GearError gearError{ car.SetGear(Gear::First) };
			SpeedError speedError{ car.SetSpeed(30) };

			car.SetGear(Gear::Second);
			car.SetSpeed(50);
			gearError = car.SetGear(Gear::Fifth);
			speedError = car.SetSpeed(150);

			Assert::IsTrue(gearError == GearError::NoError, L"Gear wasn't successfully set");
			Assert::IsTrue(speedError == SpeedError::NoError, L"Speed wasn't successfully set");
			Assert::IsTrue(car.GetDirection() == Direction::Forward, L"Direction isn't forward");
			Assert::IsTrue(car.GetGear() == Gear::Fifth, L"Car isn't at fifth gear");
			Assert::IsTrue(car.GetSpeed() == 150, L"Speed isn't 150");
		}

		TEST_METHOD(TestTryAccelerateAtNeutralGear)
		{
			Car car;
			car.TurnOnEngine();
			
			SpeedError speedError{ car.SetSpeed(20) };

			Assert::IsTrue(speedError == SpeedError::AccelerateInNeutralGear, L"Speed can't be set at neutral gear");
		}

		TEST_METHOD(TestMoveCarBackwards)
		{
			Car car;
			car.TurnOnEngine();

			GearError gearError{ car.SetGear(Gear::Reverse) };
			SpeedError speedError{ car.SetSpeed(20) };

			Assert::IsTrue(gearError == GearError::NoError, L"Gear wasn't successfully set");
			Assert::IsTrue(speedError == SpeedError::NoError, L"Speed wasn't successfully set");
			Assert::IsTrue(car.GetDirection() == Direction::Backward, L"Direction isn't backward");
			Assert::AreEqual(20, car.GetSpeed(), L"Speed isn't 20");
		}

		TEST_METHOD(TestTrySetGearWithEngineOff)
		{
			Car car;
			
			GearError gearError{ car.SetGear(Gear::First) };

			Assert::IsTrue(gearError == GearError::EngineIsOff, L"Car is switched into first gear with engine off");
		}

		TEST_METHOD(TestTrySetSpeedWithEngineOff)
		{
			Car car;

			SpeedError speedError{ car.SetSpeed(20) };

			Assert::IsTrue(speedError == SpeedError::EngineIsOff, L"Car speed is set to 20  with engine off");
		}

		TEST_METHOD(TestTrySetFirstGearAtMovingBackwards)
		{
			Car car;

			car.TurnOnEngine();
			car.SetGear(Gear::Reverse);
			car.SetSpeed(20);

			GearError gearError{ car.SetGear(Gear::First) };

			Assert::IsTrue(gearError == GearError::WrongDirection, L"Gear successfully set");
		}

		TEST_METHOD(TestTrySetFirstGearFromNeutralGearWhileMovingBackwards)
		{
			Car car;

			car.TurnOnEngine();
			car.SetGear(Gear::Reverse);
			car.SetSpeed(20);
			car.SetGear(Gear::Neutral);
			
			GearError gearError{ car.SetGear(Gear::First) };

			Assert::IsTrue(gearError == GearError::WrongDirection, L"Gear successfully set");
		}

		TEST_METHOD(TestTrySetNegativeSpeed)
		{
			Car car;

			car.TurnOnEngine();
			car.SetGear(Gear::Neutral);
			auto testedFunction = [&car]() { car.SetSpeed(-50); };

			Assert::ExpectException<std::invalid_argument>(testedFunction, L"Negative speed was set");
		}

		TEST_METHOD(TestTrySetSpeedExceedingUpperBound)
		{
			Car car;
			car.TurnOnEngine();
			car.SetGear(Gear::First);
			
			SpeedError speedError{ car.SetSpeed(std::numeric_limits<int>::max()) };

			Assert::IsTrue(speedError == SpeedError::WrongSpeed, L"Set speed exceeding upper bound");
		}

		TEST_METHOD(TestTurnOffEngine)
		{
			Car car;
			car.TurnOnEngine();

			EngineError engineError{ car.TurnOffEngine() };

			Assert::IsTrue(engineError == EngineError::NoError, L"Engine isn't off");
		}

		TEST_METHOD(TestTryTurnOffEngineWhileMoving)
		{
			Car car;

			car.TurnOnEngine();
			car.SetGear(Gear::First);
			car.SetSpeed(20);
			
			EngineError engineError{ car.TurnOffEngine() };

			Assert::IsTrue(engineError == EngineError::CarIsMoving, L"Engine was turned off while moving");
		}
	};

	TEST_CLASS(CarControllerTest)
	{
	public:
		TEST_METHOD(CanHandleEngineOnCommand)
		{
			CarTestController testController;
			testController.VerifyCommandHandling("EngineOn", HandlingStatus::Success, Gear::Neutral, 0, Direction::None, "");
		}

		TEST_METHOD(CanHandleEngineOffCommand)
		{
			CarTestController testController;
			testController.car.TurnOnEngine();
			testController.VerifyCommandHandling("EngineOff", HandlingStatus::Success, std::nullopt, std::nullopt, std::nullopt, "");
		}

		TEST_METHOD(CanHandleSetGearCommand)
		{
			CarTestController testController;
			testController.car.TurnOnEngine();
			testController.VerifyCommandHandling("SetGear 1", HandlingStatus::Success, Gear::First, 0, Direction::None, "");
		}

		TEST_METHOD(CanHandleSetSpeedCommand)
		{
			CarTestController testController;
			testController.car.TurnOnEngine();
			testController.car.SetGear(Gear::First);
			testController.VerifyCommandHandling("SetSpeed 30", HandlingStatus::Success, Gear::First, 30, Direction::Forward, "");
		}

		TEST_METHOD(CanHandleInfoCommand)
		{
			CarTestController testController;
			testController.VerifyCommandHandling("Info", HandlingStatus::Success, std::nullopt, std::nullopt, std::nullopt, 
				"Engine: Engine is off\nGear: Neutral\nDirection: None\nSpeed: 0 km/h\n");

			testController.car.TurnOnEngine();
			testController.car.SetGear(Gear::Reverse);
			testController.car.SetSpeed(20);
			testController.VerifyCommandHandling("Info", HandlingStatus::Success, Gear::Reverse, 20, Direction::Backward,
				"Engine: Engine is on\nGear: Reverse\nDirection: Backward\nSpeed: 20 km/h\n");
		}

		TEST_METHOD(CantSelectInvalidSpeed)
		{
			CarTestController testController;
			testController.car.TurnOnEngine();
			testController.car.SetGear(Gear::First);
			testController.VerifyCommandHandling("SetSpeed 50", HandlingStatus::Fail, Gear::First, 0, Direction::None, 
				"Unable to set speed: current gear doesn't allow this speed\n");
		}

		TEST_METHOD(CantTurnEngineOffWhileMoving)
		{
			CarTestController testController;
			testController.car.TurnOnEngine();
			testController.car.SetGear(Gear::First);
			testController.car.SetSpeed(20);
			testController.VerifyCommandHandling("EngineOff", HandlingStatus::Fail, Gear::First, 20, Direction::Forward,
				"Cannot turn the engine off while moving\n");
		}

		TEST_METHOD(CantAccelerateInNeutralGear)
		{
			CarTestController testController;
			testController.car.TurnOnEngine();
			testController.VerifyCommandHandling("SetSpeed 20", HandlingStatus::Fail, Gear::Neutral, 0, Direction::None,
				"Unable to set speed: acceleration in neutral speed is not allowed\n");
		}

		TEST_METHOD(CantSetReverseGearMovingBackwards)
		{
			CarTestController testController;
			testController.car.TurnOnEngine();
			testController.car.SetGear(Gear::Reverse);
			testController.car.SetSpeed(20);
			testController.car.SetGear(Gear::Neutral);
			testController.VerifyCommandHandling("SetGear -1", HandlingStatus::Fail, Gear::Neutral, 20, Direction::Backward,
				"Unable to set gear: wrong speed\n");
		}
	};
}