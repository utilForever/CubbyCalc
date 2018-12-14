#ifndef CUBBYCALC_CALCULATOR_HPP
#define CUBBYCALC_CALCULATOR_HPP

#include <Expressions/Expression.hpp>
#include <Expressions/ExpressionMaker.hpp>
#include <Variables/VariableTable.hpp>

#include <vector>

class Calculator
{
private:
	Calculator(const Calculator&);
	Calculator& operator=(const Calculator&);

	ExpressionMaker m_expMaker;
	VariableTable m_varTable;

	static const std::string m_validCommand;
	static const std::string m_numberedCommand;
	Expression m_currentExpression;
	char m_command;
	size_t m_expressionNumber;
	int m_expressionNR;
	std::vector<Expression> m_oldExpressions;

	void PrintHelp();
	void GetCommand();
	bool ValidCommand();
	void ExecuteCommand();
	void PrintExpression(std::ostream&) const;
	void EvaluateAndPrintExpression(std::ostream&) const;
	void PrintPostfix(std::ostream&) const;
	void PrintInfix(std::ostream&) const;
	void PrintTree(std::ostream&) const;
	void SetCurrentExpression();
	void ReadExpression(std::istream&);

	std::vector<std::string> SplitExpression(const std::string&, const std::string&);
public:
	Calculator();
	~Calculator();

	void Run();
};

#endif