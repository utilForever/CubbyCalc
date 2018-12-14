#ifndef CUBBYCALC_EXPRESSION_MAKER_HPP
#define CUBBYCALC_EXPRESSION_MAKER_HPP

#include <Expressions/Expression.hpp>
#include <Expressions/ExpressionTree.hpp>
#include <Variables/VariableTable.hpp>

#include <stdexcept>
#include <string>

class ExpressionMakerError : public std::logic_error
{
public:
	explicit ExpressionMakerError(const std::string& whatArg) throw()
		: logic_error(whatArg) { }
};

class ExpressionMaker
{
private:
	bool m_isTreeGenerated;
	std::string m_postfix;
	Expression m_internalExpression;
	VariableTable& m_varTable;

	ExpressionTree* MakeExpressionTree(const std::string&);

public:
	ExpressionMaker(VariableTable&);
	~ExpressionMaker();

	Expression GetExpression();
	void SetPostfix(const std::string&);
};

#endif