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

	m_variables[identifier] = std::nullopt;
	m_identifiers[identifier] = IdentifierType::Variable;
}

void Calculator::CreateFunction(const Identifier& identifier, const Expression& expression)
{
	// TODO: Добавить код
}

void Calculator::CreateFunction(const Identifier& lIdentifier, const Identifier& rIdentifier)
{
	// TODO: Добавить код
}

void Calculator::SetVariable(const Identifier& identifier, double value)
{
	// TODO: Добавить проверку на валидность идентификатора

	m_variables[identifier] = value;
}

void Calculator::SetVariable(const Identifier& lName, const Identifier& rName)
{
	// TODO: Добавить проверку что правый идентификатор не является функцией
}

const Calculator::Variables& Calculator::GetVariables() const
{
	return m_variables;
}

const Calculator::Functions& Calculator::GetFunctions() const
{
	return m_functions;
}

Calculator::Value Calculator::GetIdentifierValue(const Identifier& name) const
{
	auto it = m_variables.find(name);

	if (it == m_variables.cend())
	{
		throw std::runtime_error("Variable not found");
	};

	return it->second;
}

bool Calculator::IdentifierExists(const Identifier& identifier) const
{
	return m_identifiers.find(identifier) != m_identifiers.cend() ? true : false;
}

bool Calculator::IsValidIdentifier(const Identifier& identifier) const
{
	if (IsEmptyString(identifier) || 
		HasInvalidCharacter(identifier) || 
		std::isdigit(identifier[0]))
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