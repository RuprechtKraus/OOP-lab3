#include "Calculator.h"
#include <stdexcept>
#include <algorithm>

bool Calculator::CreateVariable(const std::string& identifier)
{
	// TODO: Добавить проверку на валидность идентификатора

	if (!VariableExists(identifier))
	{
		m_variables[identifier] = std::nullopt;
		m_identifiers[identifier] = IdentifierType::Variable;
		return true;
	}

	return false;
}

bool Calculator::CreateFunction(const std::string& identifier, const Expression& expression)
{
	//TODO: Добавить код
}

bool Calculator::CreateFunction(const std::string& lIdentifier, const std::string& rIdentifier)
{
	// TODO: Добавить код
}

void Calculator::SetVariable(const std::string& identifier, double value)
{
	// TODO: Добавить проверку на валидность идентификатора

	m_variables[identifier] = value;
}

void Calculator::SetVariable(const std::string& lName, const std::string& rName)
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

Calculator::Value Calculator::GetIdentifierValue(const std::string& name) const
{
	auto it = m_variables.find(name);

	if (it == m_variables.cend())
	{
		throw std::runtime_error("Variable not found");
	};

	return it->second;
}

bool Calculator::VariableExists(const std::string& identifier) const
{
	return m_variables.find(identifier) != m_variables.cend() ? true : false;
}

bool Calculator::FunctionExists(const std::string& identifier) const
{
	//TODO: Добавить код поиска идентификатора функции
}

bool Calculator::IsValidIdentifier(const std::string& identifier) const
{
	//TODO: Добавить код
	return false;
}