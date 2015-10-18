#ifndef EXPRESSION_MAKER_H
#define EXPRESSION_MAKER_H

#include <string>
#include <stdexcept>

#include "Expression.h"
#include "ExpressionTree.h"

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

	ExpressionTree* MakeExpressionTree(const std::string&);

public:
	ExpressionMaker();
	~ExpressionMaker();

	Expression GetExpression();
	void SetPostfix(const std::string&);
};

#endif