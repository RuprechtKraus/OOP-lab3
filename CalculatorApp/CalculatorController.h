#pragma once
#include "Calculator.h"
#include <functional>
#include <iostream>
#include <map>
#include <variant>

class CalculatorController
{
public:
	CalculatorController(Calculator& calculator, std::istream& input, std::ostream& output);

	void BeginControl();
	void ShowHelp() const;

private:
	enum class Action
	{
		CreateVariable,
		CreateFunction,
		SetVariable,
		PrintIdentifier,
		PrintVariables,
		PrintFunctions,
		ShowHelp,
		Exit
	};

	enum class ExecuteResult
	{
		Success,
		Fail,
		Exit
	};

	using Expression = Calculator::Expression;
	using Identifier = Calculator::Identifier;
	using ValueType = Calculator::ValueType;
	using Operation = Calculator::Operation;
	using Command = std::string;
	using Handler = std::function<ExecuteResult(std::istream& args)>;
	using ActionMap = std::map<Command, Action>;
	using AssignmentValue = std::variant<Identifier, ValueType>;
	using AssignmentArguments = std::pair<Identifier, AssignmentValue>;
	using FunctionCreationValue = std::variant<Identifier, Expression>;
	using FunctionCreationArguments = std::pair<Identifier, FunctionCreationValue>;

	ExecuteResult ExecuteAction(Action action, std::istream& args) const;
	ExecuteResult ExecuteHandlingExceptions(const Handler& handler, std::istream& args) const;
	ExecuteResult CreateVariable(std::istream& args) const;
	ExecuteResult CreateFunction(std::istream& args) const;
	ExecuteResult SetVariable(std::istream& args) const;
	ExecuteResult PrintIdentifierValue(std::istream& args) const;
	ExecuteResult PrintVariables(std::istream& args) const;
	ExecuteResult PrintFunctions(std::istream& args) const;
	ExecuteResult PrintHelp(std::istream& args) const;
	ExecuteResult Exit(std::istream& args) const;
	Handler GetActionHandler(Action action) const;
	AssignmentValue ParseAssignmentValue(const std::string& argument) const;
	AssignmentArguments ParseAssignmentArguments(const std::string& arguments) const;
	FunctionCreationArguments ParseFunctionCreationArguments(const std::string& arguments) const;
	FunctionCreationValue ParseFunctionCreationValue(const std::string& arguments) const;
	void InvokeSetVariable(Calculator::Identifier identifier, AssignmentValue value) const;
	void InvokeCreateFunction(Calculator::Identifier identifier, FunctionCreationValue value) const;
	Operation CharToOperation(char ch) const;
	void SetPrintPrecision() const;
	void ResetPrintPrecision() const;

	static const int m_printPrecision = 2;
	static const int m_defaultPrecision = 6;

	Calculator& m_calculator;
	std::istream& m_input;
	std::ostream& m_output;
	static ActionMap m_actionMap;
};