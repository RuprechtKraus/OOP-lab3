#include "CalculatorController.h"
#include <algorithm>

CalculatorController::ActionMap CalculatorController::m_actionMap{
	{ "var", Action::CreateVariable },
	{ "let", Action::SetVariable },
	{ "fn", Action::CreateFunction },
	{ "print", Action::PrintIdentifier },
	{ "printvars", Action::PrintVariables },
	{ "printfns", Action::PrintFunctions },
	{ "help", Action::ShowHelp },
	{ "exit", Action::Exit }
};

void ToLowerString(std::string& str);

std::optional<double> ConvertToDouble(const std::string& str);

CalculatorController::CalculatorController(Calculator& calculator, std::istream& input, std::ostream& output)
	: m_calculator(calculator)
	, m_input(input)
	, m_output(output)
{
}

void CalculatorController::BeginControl()
{
	std::string command{};
	CalculatorController::ActionMap::iterator action{};
	ExecuteResult executeResult{ ExecuteResult::Success };

	while (executeResult != ExecuteResult::Exit)
	{
		m_output << "> ";
		m_input >> command;
		ToLowerString(command);

		action = m_actionMap.find(command);
		if (action != m_actionMap.cend())
		{
			executeResult = ExecuteAction(action->second, m_input);
		}
		else
		{
			m_output << "Unknown command" << std::endl;
			m_input.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
	};
}

CalculatorController::ExecuteResult CalculatorController::ExecuteAction(
	Action action,
	std::istream& args) const
{
	Handler handler{ GetActionHandler(action) };
	return ExecuteHandlingExceptions(handler, args);
}

CalculatorController::Handler CalculatorController::GetActionHandler(Action action) const
{
	switch (action)
	{
	case CalculatorController::Action::CreateVariable:
		return std::bind(&CalculatorController::CreateVariable, this, std::placeholders::_1);
	case CalculatorController::Action::CreateFunction:
		return std::bind(&CalculatorController::CreateFunction, this, std::placeholders::_1);
	case CalculatorController::Action::SetVariable:
		return std::bind(&CalculatorController::SetVariable, this, std::placeholders::_1);
	case CalculatorController::Action::PrintIdentifier:
		return std::bind(&CalculatorController::PrintIdentifierValue, this, std::placeholders::_1);
	case CalculatorController::Action::PrintVariables:
		return std::bind(&CalculatorController::PrintVariables, this, std::placeholders::_1);
	case CalculatorController::Action::PrintFunctions:
		return std::bind(&CalculatorController::PrintFunctions, this, std::placeholders::_1);
	case CalculatorController::Action::ShowHelp:
		return std::bind(&CalculatorController::PrintHelp, this, std::placeholders::_1);
	case CalculatorController::Action::Exit:
		return std::bind(&CalculatorController::Exit, this, std::placeholders::_1);
	default:
		throw std::invalid_argument("No handler for action");
	}
}

CalculatorController::ExecuteResult CalculatorController::ExecuteHandlingExceptions(
	const CalculatorController::Handler& handler,
	std::istream& args) const
{
	try
	{
		return handler(args);
	}
	catch (const std::exception& e)
	{
		m_output << e.what() << std::endl;
		return ExecuteResult::Fail;
	}
}

CalculatorController::ExecuteResult CalculatorController::CreateVariable(
	std::istream& args) const
{
	std::string identifier{};
	args >> identifier;

	m_calculator.CreateVariable(identifier);
	return ExecuteResult::Success;
}

CalculatorController::ExecuteResult CalculatorController::CreateFunction(
	std::istream& args) const
{
	std::string arguments{};
	args >> arguments;

	auto parsedArguments = ParseFunctionCreationArguments(arguments);
	InvokeCreateFunction(parsedArguments.first, parsedArguments.second);

	return ExecuteResult::Success;
}

CalculatorController::FunctionCreationArguments CalculatorController::ParseFunctionCreationArguments(
	const std::string& arguments) const
{
	size_t pos = arguments.find('=');
	std::string identifier{ arguments.substr(0, pos) };
	auto value{ ParseFunctionCreationValue(arguments.substr(pos + 1)) };

	return { identifier, value };
}

CalculatorController::FunctionCreationValue CalculatorController::ParseFunctionCreationValue(
	const std::string& arguments) const
{
	size_t pos = arguments.find_first_of("+-*/");

	if (pos == std::string::npos)
	{
		return arguments;
	}

	Expression expression{ 
		arguments.substr(0, pos), 
		arguments.substr(pos + 1), 
		CharToOperation(arguments[pos])
	};

	return expression;
}

void CalculatorController::InvokeCreateFunction(
	Identifier identifier,
	FunctionCreationValue value) const
{
	if (std::holds_alternative<Identifier>(value))
	{
		m_calculator.CreateFunction(identifier, std::get<Identifier>(value));
	}
	else
	{
		m_calculator.CreateFunction(identifier, std::get<Expression>(value));
	}
}

CalculatorController::ExecuteResult CalculatorController::SetVariable(
	std::istream& args) const
{
	std::string arguments{};
	args >> arguments;
	AssignmentArguments assignmentArguments{ ParseAssignmentArguments(arguments) };
	InvokeSetVariable(assignmentArguments.first, assignmentArguments.second);

	return ExecuteResult::Success;
}

void CalculatorController::InvokeSetVariable(
	Identifier identifier,
	AssignmentValue value) const
{
	if (std::holds_alternative<Identifier>(value))
	{
		m_calculator.SetVariable(identifier, std::get<Identifier>(value));
	}
	else
	{
		m_calculator.SetVariable(identifier, std::get<ValueType>(value));
	}
}

CalculatorController::AssignmentArguments CalculatorController::ParseAssignmentArguments(
	const std::string& arguments) const
{
	size_t pos = arguments.find('=');
	std::string identifier{ arguments.substr(0, pos) };
	auto value = ParseAssignmentValue(arguments.substr(pos + 1));

	return { identifier, value };
}

CalculatorController::AssignmentValue CalculatorController::ParseAssignmentValue(
	const std::string& argument) const
{
	auto assignedValue = ConvertToDouble(argument);

	if (assignedValue)
	{
		return assignedValue.value();
	}
	else
	{
		return argument;
	}
}

CalculatorController::ExecuteResult CalculatorController::PrintIdentifierValue(
	std::istream& args) const
{
	std::string identifier{};
	args >> identifier;

	ValueType value{ m_calculator.GetIdentifierValue(identifier) };

	SetPrintPrecision();
	m_output << value << std::endl;
	ResetPrintPrecision();

	return ExecuteResult::Success;
}

CalculatorController::ExecuteResult CalculatorController::PrintVariables(
	std::istream& args) const
{
	auto& variables = m_calculator.GetVariables();

	SetPrintPrecision();
	for (const auto& variable : variables)
	{
		m_output << variable.first << ": " << variable.second << '\n';
	}
	ResetPrintPrecision();

	return ExecuteResult::Success;
}

CalculatorController::ExecuteResult CalculatorController::PrintFunctions(
	std::istream& args) const
{
	auto& functions = m_calculator.GetFunctions();

	SetPrintPrecision();
	for (const auto& function : functions)
	{
		m_output << function.first << ":" << m_calculator.GetIdentifierValue(function.first) << '\n';
	}
	ResetPrintPrecision();

	return ExecuteResult::Success;
}

void CalculatorController::SetPrintPrecision() const
{
	m_output.precision(m_printPrecision);
	m_output << std::fixed;
}

void CalculatorController::ResetPrintPrecision() const
{
	m_output.precision(m_printPrecision);
	m_output << std::fixed;
}

void CalculatorController::ShowHelp() const
{
	PrintHelp(m_input);
}

CalculatorController::ExecuteResult CalculatorController::PrintHelp(std::istream&) const
{
	m_output << "var <identifier>\t\t\t\t\tCreate new uninitialized variable\n"
			 << "let <identifier1>=<floating point number>\t\tCreate or set existing variable with floating number\n"
			 << "let <identifier1>=<identifier2>\t\t\t\tCreate or set existing variable with value from another one\n"
			 << "fn <identifier1>=<identifier2>\t\t\t\tCreate function copying another function\n"
			 << "fn <identifier1>=<identifier2><operation><identifier3>\tCreate function using expression\n"
			 << "print <identifier>\t\t\t\t\tPrint identirier value\n"
			 << "printvars\t\t\t\t\t\tPrint all variables\n"
			 << "printfns\t\t\t\t\t\tPrint all functions\n"
			 << "help\t\t\t\t\t\t\tShow help\n"
			 << "exit\t\t\t\t\t\t\tClose program\n"
			 << std::endl;
	return ExecuteResult::Success;
}

CalculatorController::ExecuteResult CalculatorController::Exit(std::istream&) const
{
	return ExecuteResult::Exit;
}

CalculatorController::Operation CalculatorController::CharToOperation(char ch) const
{
	switch (ch)
	{
	case '+':
		return Operation::Addition;
	case '-':
		return Operation::Substraction;
	case '*':
		return Operation::Multiplication;
	case '/':
		return Operation::Division;
	default:
		throw std::invalid_argument("Unknown operation");
	}
}

void ToLowerString(std::string& str)
{
	std::transform(str.cbegin(), str.cend(), str.begin(), [](char c) { return tolower(c); });
}

std::optional<double> ConvertToDouble(const std::string& str)
{
	char* pEnd = nullptr;
	double val = strtod(str.c_str(), &pEnd);

	if (pEnd != str.c_str() && *pEnd == '\0')
	{
		return val;
	}
	else
	{
		return std::nullopt;
	}
}