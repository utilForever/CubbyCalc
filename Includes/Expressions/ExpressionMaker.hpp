#ifndef EXPRESSION_MAKER_H
#define EXPRESSION_MAKER_H

#include <VariableTable.hpp>
#include <Expression.hpp>
#include <ExpressionTree.hpp>

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