#pragma once
#include <limits>
#include <map>
#include <optional>
#include <string>

class Calculator
{
public:
	struct Expression;

	using Identifier = std::string;
	using ValueType = double;
	using Variables = std::map<std::string, ValueType>;
	using Functions = std::map<std::string, Expression>;
	static constexpr ValueType NaNValue = std::numeric_limits<ValueType>::quiet_NaN();

	enum class Operation
	{
		None,
		Addition,
		Substraction,
		Multiplication,
		Division
	};

	struct Expression
	{
		Identifier left{};
		Identifier right{};
		Operation operation{};
	};

	void CreateVariable(const Identifier& identifier);
	void CreateFunction(const Identifier& identifier, const Expression& expression);
	void CreateFunction(const Identifier& lIdentifier, const Identifier& rIdentifier);

	void SetVariable(const Identifier& identifier, ValueType value);
	void SetVariable(const Identifier& lIdentifier, const Identifier& rIdentifier);

	ValueType GetIdentifierValue(const Identifier& identifier) const;
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
	ValueType CalculateFunction(const Identifier& identifier) const;
	ValueType Addition(const Identifier& lIdentifier, const Identifier& rIdentifier) const;
	ValueType Substraction(const Identifier& lIdentifier, const Identifier& rIdentifier) const;
	ValueType Multiplication(const Identifier& lIdentifier, const Identifier& rIdentifier) const;
	ValueType Division(const Identifier& lIdentifier, const Identifier& rIdentifier) const;
};