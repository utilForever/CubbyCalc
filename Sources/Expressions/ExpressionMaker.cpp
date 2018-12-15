#include <Commons/Constants.hpp>
#include <Expressions/ExpressionMaker.hpp>
#include <Operands/Integer.hpp>
#include <Operands/Real.hpp>
#include <Operands/Variable.hpp>
#include <Operators/BinaryOperator.hpp>
#include <Operators/Assign.hpp>
#include <Operators/Cosine.hpp>
#include <Operators/Divide.hpp>
#include <Operators/Minus.hpp>
#include <Operators/Multiply.hpp>
#include <Operators/Plus.hpp>
#include <Operators/Power.hpp>
#include <Operators/Sine.hpp>
#include <Operators/Tangent.hpp>

#include <algorithm>
#include <sstream>
#include <stack>
#include <string>
#include <vector>

ExpressionMaker::ExpressionMaker(VariableTable& varTable)
	: m_isTreeGenerated(false), m_postfix(""), m_internalExpression(), m_varTable(varTable)
{ }

ExpressionMaker::~ExpressionMaker()
{ }

void ExpressionMaker::SetPostfix(const std::string& postfix)
{
	m_postfix = postfix;
	m_isTreeGenerated = false;
}

Expression ExpressionMaker::GetExpression()
{
	if (m_postfix == "")
	{
		throw ExpressionMakerError("Postfix is empty");
	}
	else if (!m_isTreeGenerated)
	{
		Expression e(MakeExpressionTree(m_postfix));
		m_internalExpression = e;
		m_isTreeGenerated = true;
	}

	return m_internalExpression;
}

ExpressionTree* ExpressionMaker::MakeExpressionTree(const std::string& postfix)
{
	std::stack<ExpressionTree*> treeStack;
	std::string token;
	std::istringstream iss(postfix);

	while (iss >> token)
	{
		if (token == "u-")
		{
			ExpressionTree* rhs = treeStack.top();
			treeStack.pop();

			treeStack.push(new UnaryMinus(rhs));
		}
		else if (token == "sin")
		{
			ExpressionTree* rhs = treeStack.top();
			treeStack.pop();

			treeStack.push(new Sine(rhs));
		}
		else if (token == "cos")
		{
			ExpressionTree* rhs = treeStack.top();
			treeStack.pop();

			treeStack.push(new Cosine(rhs));
		}
		else if (token == "tan")
		{
			ExpressionTree* rhs = treeStack.top();
			treeStack.pop();

			treeStack.push(new Tangent(rhs));
		}
		else if (std::find(operators.begin(), operators.end(), token) != operators.end())
		{
			ExpressionTree* rhs = treeStack.top();
			treeStack.pop();
			ExpressionTree* lhs = treeStack.top();
			treeStack.pop();

			if (token == "^")
			{
				treeStack.push(new Power(lhs, rhs));
			}
			else if (token == "*")
			{
				treeStack.push(new Multiply(lhs, rhs));
			}
			else if (token == "/")
			{
				treeStack.push(new Divide(lhs, rhs));
			}
			else if (token == "+")
			{
				treeStack.push(new Plus(lhs, rhs));
			}
			else if (token == "-")
			{
				treeStack.push(new BinaryMinus(lhs, rhs));
			}
			else if (token == "=")
			{
				treeStack.push(new Assign(lhs, rhs, m_varTable));
			}
		}
		else if (token.find_first_not_of(integer_chars) == std::string::npos)
		{
			treeStack.push(new Integer(atoi(token.c_str())));
		}
		else if (token.find_first_not_of(real_chars) == std::string::npos)
		{
			treeStack.push(new Real(atof(token.c_str())));
		}
		else if (token.find_first_not_of(identifier_chars) == std::string::npos)
		{
			treeStack.push(new Variable(token, m_varTable));
		}
		else
		{
			while (!treeStack.empty())
			{
				delete treeStack.top();
				treeStack.pop();
			}

			throw ExpressionMakerError("Invalid Postfix");
		}
	}

	if (treeStack.empty())
	{
		throw ExpressionMakerError("Invalid Postfix");
	}

	if (treeStack.size() > 1)
	{
		while (!treeStack.empty())
		{
			delete treeStack.top();
			treeStack.pop();
		}

		throw ExpressionMakerError("Invalid Postfix");
	}

	return treeStack.top();
}
