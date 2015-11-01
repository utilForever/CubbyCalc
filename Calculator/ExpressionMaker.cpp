#include <sstream>
#include <vector>
#include <string>
#include <stack>
#include <map>

#include "ExpressionMaker.h"

namespace
{
	const char* ops[] = { "+", "-", "*", "/", "=", "^", "u-", "sin", "cos", "tan", "(" };
	const int init_input_priority[] = { 4, 4, 5, 5, 1, 6, 7, 7, 7, 7, 8 };
	const int init_stack_priority[] = { 4, 4, 5, 5, 1, 6, 7, 7, 7, 7, 0 };
	const int n_ops= sizeof(ops) / sizeof(char*);

	const std::vector<std::string> operators(ops, ops + n_ops);

	const std::string digits("0123456789");
	const std::string integer_chars(digits);
	const std::string real_chars(digits + '.');
	const std::string identifier_chars("abcdefghijklmnopqrstuvwxyz");
	const std::string operand_chars(identifier_chars + digits + '.');

	typedef std::map<std::string, int> priority_table;

	priority_table init_priority_table(const char* ops[], const int* priority, const int n_ops)
	{
		priority_table temp;

		for (int i = 0; i < n_ops; ++i)
		{
			temp.insert(std::make_pair(std::string(ops[i]), priority[i]));
		}

		return temp;
	}

	const priority_table input_priority = init_priority_table(ops, init_input_priority, n_ops);
	const priority_table stack_priority = init_priority_table(ops, init_stack_priority, n_ops);
}

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

			treeStack.push(new UnaryMinus(rhs));
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
