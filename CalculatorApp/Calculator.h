#pragma once
#include <map>
#include <optional>
#include <string>

class Calculator
{
public:
	struct Expression;

	using Identifier = std::string;
	using Value = std::optional<double>;
	using Variables = std::map<std::string, std::optional<double>>;
	using Functions = std::map<std::string, Expression>;

	enum class Operation
	{
		Addition,
		Substraction,
		Multiplication,
		Division
	};

	struct Expression
	{
		Identifier left;
		Identifier right;
		Operation operation;
	};

	void CreateVariable(const Identifier& identifier);
	void CreateFunction(const Identifier& identifier, const Expression& expression);
	void CreateFunction(const Identifier& lIdentifier, const Identifier& rIdentifier);

	void SetVariable(const Identifier& identifier, double value);
	void SetVariable(const Identifier& lIdentifier, const Identifier& rIdentifier);

	Value GetIdentifierValue(const Identifier& identifier) const;
	const Variables& GetVariables() const;
	const Functions& GetFunctions() const;

	bool IdentifierExists(const Identifier& identifier) const;

private:
	enum class IdentifierType;
	using Identifiers = std::map<std::string, IdentifierType>;

	Identifiers m_identifiers{};
	Variables m_variables{};
	Functions m_functions{};

	bool IsValidIdentifier(const Identifier& identifier) const;
};