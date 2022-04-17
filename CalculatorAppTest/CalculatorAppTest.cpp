#include "pch.h"
#include "CppUnitTest.h"
#include "../CalculatorApp/Calculator.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CalculatorAppTest
{
	TEST_CLASS(CalculatorAppTest)
	{
	public:
		
		TEST_METHOD(CanCreateVariable)
		{
			Calculator calc{};

			calc.CreateVariable("x");
			calc.CreateVariable("square_root");

			Assert::IsTrue(calc.IdentifierExists("x"), L"Variable wasn't created");
			Assert::IsTrue(calc.IdentifierExists("square_root"), L"Variable wasn't created");
		}

		TEST_METHOD(CantCreateExistingVariable)
		{
			Calculator calc{};

			auto testedFunction = [&calc]() { calc.CreateVariable("x"); };

			calc.CreateVariable("x");
			Assert::ExpectException<std::runtime_error>(testedFunction, 
				L"Created existing variable");
		}

		TEST_METHOD(CantCreateVariableWithInvalidIdentifier)
		{
			Calculator calc{};

			auto createVarWithDotInName = [&calc]() { calc.CreateVariable("has.dot"); };
			auto createVarWithFirstDigitInName = [&calc]() { calc.CreateVariable("7 stars"); };
			auto createVarWithSpaceInName = [&calc]() { calc.CreateVariable("big number"); };

			Assert::ExpectException<std::invalid_argument>(createVarWithDotInName, 
				L"Created variable with invalid identifier");
			Assert::ExpectException<std::invalid_argument>(createVarWithFirstDigitInName, 
				L"Created variable with invalid identifier");
			Assert::ExpectException<std::invalid_argument>(createVarWithSpaceInName,
				L"Created variable with invalid identifier");
		}

		TEST_METHOD(CanSetExistingVariable)
		{
			Calculator calc{};

			calc.CreateVariable("x");
			calc.SetVariable("x", 5);

			Assert::IsTrue(calc.GetIdentifierValue("x") == 5, 
				L"Identifier value is not as expected");
		}

		TEST_METHOD(CanSetExistingVariableWithIdentifier)
		{
			Calculator calc{};

			calc.CreateVariable("x");
			calc.SetVariable("x", 5);

			calc.CreateVariable("y");
			calc.SetVariable("y", "x");

			Assert::IsTrue(calc.GetIdentifierValue("y") == 5,
				L"Identifier value is not as expected");
		}

		TEST_METHOD(CanSetNotExistingVariable)
		{
			Calculator calc{};
			calc.SetVariable("x", 10);
			Assert::IsTrue(calc.GetIdentifierValue("x") == 10,
				L"Identifier value is not as expected");
		}

		TEST_METHOD(CanSetNotExistingVariableWithIdentifier)
		{
			Calculator calc{};
			calc.SetVariable("x", 10);
			calc.SetVariable("y", "x");
			Assert::IsTrue(calc.GetIdentifierValue("y") == 10, 
				L"Identifier value is not as expected");
		}

		TEST_METHOD(GetValueOfUninitializedVariable)
		{
			Calculator calc{};
			calc.CreateVariable("x");
			Assert::IsFalse(calc.GetIdentifierValue("x").has_value(), 
				L"Uninitialized identifer has value");
		}

		TEST_METHOD(CanCreateFunctionUsingExpression)
		{
			Calculator calc{};
			Calculator::Expression expression{
				"x",
				"y",
				Calculator::Operation::Addition
			};

			calc.CreateVariable("x");
			calc.CreateVariable("y");
			calc.CreateFunction("XplusY", expression);

			Assert::IsTrue(calc.IdentifierExists("XplusY"));
		}

		TEST_METHOD(GetValueOfVariableSetWithFunction)
		{
			Calculator calc{};
			Calculator::Expression expression{
				"x",
				"y",
				Calculator::Operation::Addition
			};

			calc.SetVariable("x", 5);
			calc.SetVariable("y", 10);
			calc.CreateFunction("XplusY", expression);
			calc.SetVariable("sum", "XplusY");

			Assert::IsTrue(calc.GetIdentifierValue("sum") == 15, 
				L"Function result is not as expected");
		}

		TEST_METHOD(CanCreateFunctionFromAnotherIdentifier)
		{
			Calculator calc{};
			Calculator::Expression expression{
				"x",
				"y",
				Calculator::Operation::Addition
			};

			calc.CreateVariable("x");
			calc.CreateVariable("y");
			calc.CreateFunction("XplusY", expression);
			calc.CreateFunction("YplusX", "XplusY");

			Assert::IsTrue(calc.IdentifierExists("YplusX"));
		}

		TEST_METHOD(CantCreateFunctionWithExisitingIdentifier)
		{
			Calculator calc{};
			Calculator::Expression expression{
				"x",
				"y",
				Calculator::Operation::Addition
			};

			auto testedFunction = [&calc, &expression]() { calc.CreateFunction("XplusY", expression); };

			calc.CreateVariable("x");
			calc.CreateVariable("y");
			calc.CreateFunction("XplusY", expression);

			Assert::ExpectException<std::runtime_error>(testedFunction, 
				L"Created function with existing identifier");
		}

		TEST_METHOD(CantCreateFunctionWithInvalidIdentifier)
		{
			Calculator calc{};

			auto createFunWithDotInName = [&calc]() { 
				calc.CreateFunction("Xplus.Y", { "x", "y", Calculator::Operation::Addition }); 
			};
			auto createFunWithFirstDigitInName = [&calc]() { 
				calc.CreateFunction("7_times_x", { "seven", "x", Calculator::Operation::Multiplication}); 
			};
			auto createFunWithSpaceInName = [&calc]() { 
				calc.CreateFunction("X minus Y", { "x", "y", Calculator::Operation::Substraction }); 
			};

			calc.CreateVariable("x");
			calc.CreateVariable("y");
			calc.CreateVariable("seven");

			Assert::ExpectException<std::invalid_argument>(createFunWithDotInName,
				L"Created function with invalid identifier");
			Assert::ExpectException<std::invalid_argument>(createFunWithFirstDigitInName,
				L"Created function with invalid identifier");
			Assert::ExpectException<std::invalid_argument>(createFunWithSpaceInName,
				L"Created function with invalid identifier");
		}

		TEST_METHOD(CantCreateFunctionWithNotExistingArgumentIdentifiers)
		{
			Calculator calc{};

			auto testedFunction = [&calc]() { 
				calc.CreateFunction("XplusY", { "x", "y", Calculator::Operation::Addition }); 
			};

			Assert::ExpectException<std::runtime_error>(testedFunction, 
				L"Created function with not existing argument identifiers");
		}

		TEST_METHOD(CalculateFunctionWithInitializedVariables)
		{
			Calculator calc{};

			calc.SetVariable("x", 5);
			calc.SetVariable("y", 10);
			calc.CreateFunction("XmultiplyY", { "x", "y", Calculator::Operation::Multiplication });

			Assert::IsTrue(calc.GetIdentifierValue("XmultiplyY") == 50, 
				L"Function result is not as expected");
		}

		TEST_METHOD(CalculateFunctionWithUninitializedVariables)
		{
			Calculator calc{};

			calc.CreateVariable("x");
			calc.CreateVariable("y");
			calc.CreateFunction("XmultiplyY", { "x", "y", Calculator::Operation::Multiplication });

			Assert::IsFalse(calc.GetIdentifierValue("XmultiplyY").has_value(),
				L"Function result is not as expected");
		}

		TEST_METHOD(CalculateFunctionWithAnotherFunctionAsOneIdentifier)
		{
			Calculator calc{};

			calc.SetVariable("x", 5);
			calc.SetVariable("y", 10);
			calc.SetVariable("z", 20);
			calc.CreateFunction("XmultiplyY", { "x", "y", Calculator::Operation::Multiplication });
			calc.CreateFunction("XYplusZ", { "XmultiplyY", "z", Calculator::Operation::Addition });

			Assert::IsTrue(calc.GetIdentifierValue("XYplusZ") == 70,
				L"Function result is not as expected");
		}

		TEST_METHOD(CalculateFunctionWithAnotherFunctionThatHasNoResult)
		{
			Calculator calc{};

			calc.CreateVariable("x");
			calc.CreateVariable("y");
			calc.CreateFunction("XmultiplyY", { "x", "y", Calculator::Operation::Multiplication });

			auto testedFunction = [&calc]() { 
				calc.CreateFunction("XYplusZ", { "XmultiplyY", "z", Calculator::Operation::Addition }); 
			};

			Assert::ExpectException<std::runtime_error>(testedFunction, L"Function result is not as expected");
		}
	};
}
