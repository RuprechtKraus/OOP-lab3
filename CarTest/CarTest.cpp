#include "pch.h"
#include "CppUnitTest.h"
#include "../CarClassDesigning/Car.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CarTest
{
	TEST_CLASS(CarTest)
	{
	public:
		
		TEST_METHOD(TestTurnGearOn)
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
			Assert::IsTrue(car.IsTurnedOn(), L"Engine isn't on");

			bool gearSetSuccess{ car.SetGear(Gear::First) };

			Assert::IsTrue(car.IsTurnedOn(), L"Engine isn't on");
			Assert::IsTrue(car.GetDirection() == Direction::None, L"Direction isn't None");
			Assert::IsTrue(car.GetGear() == Gear::First, L"Car isn't at first gear");
			Assert::IsTrue(car.GetSpeed() == 0, L"Speed isn't 0");
		}

		TEST_METHOD(TestSetAllGearsInTurn)
		{
			Car car;

			car.TurnOnEngine();
			Assert::IsTrue(car.IsTurnedOn(), L"Engine isn't on");

			bool gearSetSuccess{ car.SetGear(Gear::First) };
			bool speedSetSuccess{ car.SetSpeed(30) };

			Assert::IsTrue(gearSetSuccess, L"Gear wasn't successfully set");
			Assert::IsTrue(speedSetSuccess, L"Speed wasn't successfully set");
			Assert::AreEqual(30, car.GetSpeed(), L"Speed isn't 30");

			gearSetSuccess = car.SetGear(Gear::Second);
			speedSetSuccess = car.SetSpeed(40);

			Assert::IsTrue(gearSetSuccess, L"Gear wasn't successfully set");
			Assert::IsTrue(speedSetSuccess, L"Speed wasn't successfully set");
			Assert::IsTrue(car.GetGear() == Gear::Second, L"Car isn't at second gear");
			Assert::AreEqual(40, car.GetSpeed(), L"Speed isn't 30");

			gearSetSuccess = car.SetGear(Gear::Third);
			speedSetSuccess = car.SetSpeed(50);

			Assert::IsTrue(gearSetSuccess, L"Gear wasn't successfully set");
			Assert::IsTrue(speedSetSuccess, L"Speed wasn't successfully set");
			Assert::IsTrue(car.GetGear() == Gear::Third, L"Car isn't at third gear");
			Assert::AreEqual(40, car.GetSpeed(), L"Speed isn't 50");

			gearSetSuccess = car.SetGear(Gear::Fourth);
			speedSetSuccess = car.SetSpeed(70);

			Assert::IsTrue(gearSetSuccess, L"Gear wasn't successfully set");
			Assert::IsTrue(speedSetSuccess, L"Speed wasn't successfully set");
			Assert::IsTrue(car.GetGear() == Gear::Fourth, L"Car isn't at fourth gear");
			Assert::AreEqual(70, car.GetSpeed(), L"Speed isn't 70");

			gearSetSuccess = car.SetGear(Gear::Fifth);
			speedSetSuccess = car.SetSpeed(150);

			Assert::IsTrue(gearSetSuccess, L"Gear wasn't successfully set");
			Assert::IsTrue(speedSetSuccess, L"Speed wasn't successfully set");
			Assert::IsTrue(car.GetGear() == Gear::Fifth, L"Car isn't at fifth gear");
			Assert::AreEqual(150, car.GetSpeed(), L"Speed isn't 150");
		}
	};
}