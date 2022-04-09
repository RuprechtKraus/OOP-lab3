#include "pch.h"
#include "CppUnitTest.h"
#include "../CarClassDesigning/Car.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

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
}