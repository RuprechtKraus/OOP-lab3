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

			bool gearSetSuccess{ car.SetGear(Gear::First) };

			Assert::IsTrue(car.IsTurnedOn(), L"Engine isn't on");
			Assert::IsTrue(car.GetDirection() == Direction::None, L"Direction isn't None");
			Assert::IsTrue(car.GetGear() == Gear::First, L"Car isn't at first gear");
			Assert::IsTrue(car.GetSpeed() == 0, L"Speed isn't 0");
		}

		TEST_METHOD(TestSetReverseGear)
		{
			Car car;
			car.TurnOnEngine();

			bool gearSetSuccess = car.SetGear(Gear::Reverse);

			Assert::IsTrue(gearSetSuccess, L"Gear wasn't successfully set");
			Assert::IsTrue(car.GetGear() == Gear::Reverse, L"Car isn't at Reverse gear");
		}

		TEST_METHOD(TestSetAllGearsInTurn)
		{
			Car car;
			car.TurnOnEngine();

			bool gearSetSuccess{ car.SetGear(Gear::First) };
			bool speedSetSuccess{ car.SetSpeed(30) };

			Assert::IsTrue(car.GetDirection() == Direction::Forward, L"Direction isn't forward");
			Assert::IsTrue(gearSetSuccess, L"Gear wasn't successfully set");
			Assert::IsTrue(speedSetSuccess, L"Speed wasn't successfully set");
			Assert::AreEqual(30, car.GetSpeed(), L"Speed isn't 30");

			gearSetSuccess = car.SetGear(Gear::Second);
			speedSetSuccess = car.SetSpeed(40);

			Assert::IsTrue(car.GetDirection() == Direction::Forward, L"Direction isn't forward");
			Assert::IsTrue(gearSetSuccess, L"Gear wasn't successfully set");
			Assert::IsTrue(speedSetSuccess, L"Speed wasn't successfully set");
			Assert::IsTrue(car.GetGear() == Gear::Second, L"Car isn't at second gear");
			Assert::AreEqual(40, car.GetSpeed(), L"Speed isn't 30");

			gearSetSuccess = car.SetGear(Gear::Third);
			speedSetSuccess = car.SetSpeed(50);

			Assert::IsTrue(car.GetDirection() == Direction::Forward, L"Direction isn't forward");
			Assert::IsTrue(gearSetSuccess, L"Gear wasn't successfully set");
			Assert::IsTrue(speedSetSuccess, L"Speed wasn't successfully set");
			Assert::IsTrue(car.GetGear() == Gear::Third, L"Car isn't at third gear");
			Assert::AreEqual(40, car.GetSpeed(), L"Speed isn't 50");

			gearSetSuccess = car.SetGear(Gear::Fourth);
			speedSetSuccess = car.SetSpeed(70);

			Assert::IsTrue(car.GetDirection() == Direction::Forward, L"Direction isn't forward");
			Assert::IsTrue(gearSetSuccess, L"Gear wasn't successfully set");
			Assert::IsTrue(speedSetSuccess, L"Speed wasn't successfully set");
			Assert::IsTrue(car.GetGear() == Gear::Fourth, L"Car isn't at fourth gear");
			Assert::AreEqual(70, car.GetSpeed(), L"Speed isn't 70");

			gearSetSuccess = car.SetGear(Gear::Fifth);
			speedSetSuccess = car.SetSpeed(150);

			Assert::IsTrue(car.GetDirection() == Direction::Forward, L"Direction isn't forward");
			Assert::IsTrue(gearSetSuccess, L"Gear wasn't successfully set");
			Assert::IsTrue(speedSetSuccess, L"Speed wasn't successfully set");
			Assert::IsTrue(car.GetGear() == Gear::Fifth, L"Car isn't at fifth gear");
			Assert::AreEqual(150, car.GetSpeed(), L"Speed isn't 150");
		}

		TEST_METHOD(TestSetGearFromSecondToFifth)
		{
			Car car;
			car.TurnOnEngine();

			bool gearSetSuccess{ car.SetGear(Gear::First) };
			bool speedSetSuccess{ car.SetSpeed(30) };

			car.SetGear(Gear::Second);
			car.SetSpeed(50);
			gearSetSuccess = car.SetGear(Gear::Fifth);
			speedSetSuccess = car.SetSpeed(150);

			Assert::IsTrue(gearSetSuccess, L"Gear wasn't successfully set");
			Assert::IsTrue(speedSetSuccess, L"Speed wasn't successfully set");
			Assert::IsTrue(car.GetDirection() == Direction::Forward, L"Direction isn't forward");
			Assert::IsTrue(car.GetGear() == Gear::Fifth, L"Car isn't at fifth gear");
			Assert::IsTrue(car.GetSpeed() == 150, L"Speed isn't 150");
		}

		TEST_METHOD(TestTryAccelerateAtNeutralGear)
		{
			Car car;
			car.TurnOnEngine();
			
			bool setSpeedSuccess{ car.SetSpeed(20) };

			Assert::IsFalse(setSpeedSuccess, L"Speed can't be set at neutral gear");
		}

		TEST_METHOD(TestMoveCarBackwards)
		{
			Car car;
			car.TurnOnEngine();

			bool gearSetSuccess{ car.SetGear(Gear::Reverse) };
			bool speedSetSuccess{ car.SetSpeed(20) };

			Assert::IsTrue(gearSetSuccess, L"Gear wasn't successfully set");
			Assert::IsTrue(speedSetSuccess, L"Speed wasn't successfully set");
			Assert::IsTrue(car.GetDirection() == Direction::Backward, L"Direction isn't backward");
			Assert::AreEqual(20, car.GetSpeed(), L"Speed isn't 20");
		}


		TEST_METHOD(TestTrySetGearWithEngineOff)
		{
			Car car;
			
			bool gearSetSuccess{ car.SetGear(Gear::First) };

			Assert::IsFalse(gearSetSuccess, L"Car is switched into first gear with engine off");
		}


		TEST_METHOD(TestTrySetSpeedWithEngineOff)
		{
			Car car;

			bool speedSetSuccess{ car.SetSpeed(20) };

			Assert::IsFalse(speedSetSuccess, L"Car speed is set to 20  with engine off");
		}

		TEST_METHOD(TestTrySetFirstGearAtMovingBackwards)
		{
			Car car;

			car.TurnOnEngine();
			car.SetGear(Gear::Reverse);
			car.SetSpeed(20);

			bool gearSetSuccess{ car.SetGear(Gear::First) };

			Assert::IsFalse(gearSetSuccess, L"Gear successfully set");
		}


		TEST_METHOD(TestTrySetFirstGearFromNeutralGearWhileMovingBackwards)
		{
			Car car;

			car.TurnOnEngine();
			car.SetGear(Gear::Reverse);
			car.SetSpeed(20);
			car.SetGear(Gear::Neutral);
			
			bool gearSetSuccess{ car.SetGear(Gear::First) };

			Assert::IsFalse(gearSetSuccess, L"Gear successfully set");
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
			
			bool speedSetSuccess{ car.SetSpeed(std::numeric_limits<int>::max()) };

			Assert::IsFalse(speedSetSuccess, L"Set speed exceeding upper bound");
		}

		TEST_METHOD(TestTurnOffEngine)
		{
			Car car;
			car.TurnOnEngine();

			bool turnOffEngineSuccess{ car.TurnOffEngine() };

			Assert::IsTrue(turnOffEngineSuccess, L"Engine isn't off");
		}

		TEST_METHOD(TestTryTurnOffEngineWhileMoving)
		{
			Car car;

			car.TurnOnEngine();
			car.SetSpeed(20);
			
			bool turnOffEngineSuccess{ car.TurnOffEngine() };

			Assert::IsFalse(turnOffEngineSuccess, L"Engine was turned off while moving");
		}
	};
}