#include "Calculator.h"
#include <algorithm>
#include <stdexcept>

enum class Calculator::IdentifierType
{
	Variable,
	Function
};

bool IsEmptyString(const std::string& str);

bool HasInvalidCharacter(const std::string& str);

void Calculator::CreateVariable(const Identifier& identifier)
{
	if (!IsValidIdentifier(identifier))
	{
		throw std::invalid_argument("Invalid identifier");
	}

	if (IdentifierExists(identifier))
	{
		throw std::runtime_error("Identifier already exists");
	}

	m_variables[identifier] = NaNValue;
	m_identifiers[identifier] = IdentifierType::Variable;
}

void Calculator::CreateFunction(const Identifier& identifier, const Expression& expression)
{
	if (!IsValidIdentifier(identifier))
	{
		throw std::invalid_argument("Invalid identifier");
	}

	if (IdentifierExists(identifier))
	{
		throw std::runtime_error("Identifier already exists");
	}

	if (!IdentifierExists(expression.left) || !IdentifierExists(expression.right))
	{
		throw std::runtime_error("Expression has not existing identifiers");
	}

	m_functions[identifier] = expression;
	m_identifiers[identifier] = IdentifierType::Function;
}

void Calculator::CreateFunction(const Identifier& lIdentifier, const Identifier& rIdentifier)
{
	if (!IsValidIdentifier(lIdentifier))
	{
		throw std::invalid_argument("Invalid identifier");
	}

	if (IdentifierExists(lIdentifier))
	{
		throw std::runtime_error("Identifier already exists");
	}

	if (!IdentifierExists(rIdentifier))
	{
		throw std::runtime_error("Right identifier doesn't exist");
	}

	if (m_identifiers[rIdentifier] == IdentifierType::Variable)
	{
		m_identifiers[lIdentifier] = IdentifierType::Function;
		m_functions[lIdentifier] = { rIdentifier, "", Operation::None };
	}
	else
	{
		m_identifiers[lIdentifier] = IdentifierType::Function;
		m_functions[lIdentifier] = m_functions[rIdentifier];
	}
}

void Calculator::SetVariable(const Identifier& identifier, ValueType value)
{
	if (!IsValidIdentifier(identifier))
	{
		throw std::invalid_argument("Invalid identifier");
	}

	m_identifiers[identifier] = IdentifierType::Variable;
	m_variables[identifier] = value;
}

void Calculator::SetVariable(const Identifier& lIdentifier, const Identifier& rIdentifier)
{
	if (!IsValidIdentifier(lIdentifier))
	{
		throw std::invalid_argument("Invalid identifier");
	}

	if (!IdentifierExists(rIdentifier))
	{
		throw std::runtime_error("Right identifier doesn't exist");
	}

	if (IdentifierExists(lIdentifier) && m_identifiers[lIdentifier] == IdentifierType::Function)
	{
		throw std::runtime_error("Left identifier is function");
	}

	if (m_identifiers[rIdentifier] == IdentifierType::Variable)
	{
		m_identifiers[lIdentifier] = IdentifierType::Variable;
		m_variables[lIdentifier] = m_variables[rIdentifier];
	}
	else
	{
		m_identifiers[lIdentifier] = IdentifierType::Variable;
		m_variables[lIdentifier] = CalculateFunction(rIdentifier);
	}
}

const Calculator::Variables& Calculator::GetVariables() const
{
	return m_variables;
}

const Calculator::Functions& Calculator::GetFunctions() const
{
	return m_functions;
}

Calculator::ValueType Calculator::GetIdentifierValue(const Identifier& identifier) const
{
	if (!IdentifierExists(identifier))
	{
		throw std::runtime_error("Identifier doesn't exist");
	}

	if (m_identifiers.at(identifier) == IdentifierType::Variable)
	{
		return m_variables.at(identifier);
	}
	else
	{
		return CalculateFunction(identifier);
	}
}

Calculator::ValueType Calculator::CalculateFunction(const Identifier& identifier) const
{
	auto& expression{ m_functions.at(identifier) };

	switch (expression.operation)
	{
	case Operation::None:
		return GetIdentifierValue(expression.left);
	case Operation::Addition:
		return Addition(expression.left, expression.right);
	case Operation::Substraction:
		return Substraction(expression.left, expression.right);
	case Operation::Multiplication:
		return Multiplication(expression.left, expression.right);
	case Operation::Division:
		return Division(expression.left, expression.right);
	default:
		throw std::invalid_argument("Unknown operation");
	}
}

Calculator::ValueType Calculator::Addition(
	const Identifier& lIdentifier,
	const Identifier& rIdentifier) const
{
	return GetIdentifierValue(lIdentifier) + GetIdentifierValue(rIdentifier);
}

Calculator::ValueType Calculator::Substraction(
	const Identifier& lIdentifier,
	const Identifier& rIdentifier) const
{
	return GetIdentifierValue(lIdentifier) - GetIdentifierValue(rIdentifier);
}

Calculator::ValueType Calculator::Multiplication(
	const Identifier& lIdentifier,
	const Identifier& rIdentifier) const
{
	return GetIdentifierValue(lIdentifier) * GetIdentifierValue(rIdentifier);
}

Calculator::ValueType Calculator::Division(
	const Identifier& lIdentifier,
	const Identifier& rIdentifier) const
{
	ValueType left = GetIdentifierValue(lIdentifier);
	ValueType right = GetIdentifierValue(rIdentifier);

	if (right == 0)
	{
		return NaNValue;
	}

	return left / right;
}

bool Calculator::IdentifierExists(const Identifier& identifier) const
{
	return m_identifiers.find(identifier) != m_identifiers.cend();
}

bool Calculator::IsValidIdentifier(const Identifier& identifier) const
{
	if (IsEmptyString(identifier) || HasInvalidCharacter(identifier) || std::isdigit(identifier[0]))
	{
		return false;
	};

	return true;
}

bool IsEmptyString(const std::string& str)
{
	return str.empty() || str.find_first_not_of(' ') == std::string::npos;
}

bool HasInvalidCharacter(const std::string& str)
{
	return std::find_if(str.cbegin(), str.cend(), [](char c) {
		return !std::isalnum(c) && c != '_';
	}) != str.cend();
}