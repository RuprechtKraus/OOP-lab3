#include "pch.h"
#include "CppUnitTest.h"
#include "../CalculatorApp/Calculator.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

class CalculatorTestController
{
public:
	CalculatorTestController()
		: m_calculator(Calculator())
	{
	}

	void VerifyCreateVariableCommand(const std::string& name)
	{
		bool variableExists{ m_calculator.VariableExists(name) };
		bool variableCreated{ m_calculator.CreateVariable(name) };

		Assert::IsTrue(!variableExists == variableCreated, L"Unable to create variable");
	}

private:
	Calculator m_calculator;
};

namespace CalculatorAppTest
{
	TEST_CLASS(CalculatorAppTest)
	{
	public:
		
		TEST_METHOD(CanCreateVariable)
		{
			CalculatorTestController testController{};
			testController.VerifyCreateVariableCommand("x");
		}

		TEST_METHOD(CantCreateExistingVariable)
		{
			CalculatorTestController testController{};
			testController.VerifyCreateVariableCommand("x");
			testController.VerifyCreateVariableCommand("x");
		}

		TEST_METHOD(GetVariables)
		{
			Calculator calculator{};
		}
	};
}
