#pragma once
#include <optional>
#include <map>
#include <string>

class Calculator
{
private:
	enum class IdentifierType
	{
		Variable,
		Function
	};

public:
	enum class Operation
	{
		Addition,
		Substraction,
		Multiplication,
		Division
	};

	struct Expression
	{
		std::string leftOperand;
		std::string rightOperand;
		Operation operation;
	};

	using Value = std::optional<double>;
	using Identifiers = std::map<std::string, IdentifierType>;
	using Variables = std::map<std::string, std::optional<double>>;
	using Functions = std::map<std::string, Expression>;

	bool CreateVariable(const std::string& identifier);
	bool CreateFunction(const std::string& identifier, const Expression& expression);
	bool CreateFunction(const std::string& lIdentifier, const std::string& rIdentifier);

	void SetVariable(const std::string& identifier, double value);
	void SetVariable(const std::string& lIdentifier, const std::string& rIdentifier);

	Value GetIdentifierValue(const std::string& identifier) const;
	const Variables& GetVariables() const;
	const Functions& GetFunctions() const;

	bool VariableExists(const std::string& identifier) const;
	bool FunctionExists(const std::string& identifier) const;

private:
	Identifiers m_identifiers{};
	Variables m_variables{};
	Functions m_functions{};

	bool IsValidIdentifier(const std::string& identifier) const;
};