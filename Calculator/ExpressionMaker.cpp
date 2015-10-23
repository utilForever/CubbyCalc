#include <sstream>
#include <vector>
#include <string>
#include <stack>
#include <map>

#include "ExpressionMaker.h"

namespace
{
	const char* ops[]				= { "+", "-", "*", "/", "=", "^" };
	const int init_input_priority[]	= {  3,   3,   5,   5,   2,   8  };
	const int init_stack_priority[]	= {  4,   4,   6,   6,   1,   7  };
	const int n_ops= sizeof(ops) / sizeof(char*);

	const std::vector<std::string> operators(ops, ops + n_ops);

	const std::string digits("0123456789");
	const std::string integer_chars(digits);
	const std::string real_chars(digits + '.');
	const std::string identifier_chars("abcdefghijklmnopqrstuvwxyz");
	const std::string operand_chars(identifier_chars + digits + '.');

	using priority_table = std::map<std::string, int>;

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

ExpressionMaker::ExpressionMaker()
	: m_isTreeGenerated(false), m_postfix(""), m_internalExpression()
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
		if (std::find(operators.begin(), operators.end(), token) != operators.end())
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
				treeStack.push(new Minus(lhs, rhs));
			}
			else if (token == "=")
			{
				treeStack.push(new Assign(lhs, rhs));
			}
		}
		else if (token.find_first_not_of(integer_chars) == std::string::npos)
		{
			
		}
	}
}
