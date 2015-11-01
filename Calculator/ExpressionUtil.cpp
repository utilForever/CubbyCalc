#include <stack>
#include <vector>
#include <sstream>

#include "ExpressionTree.h"
#include "ExpressionUtil.h"

namespace
{
	const char* ops[] = { "+", "-", "*", "/", "=", "^", "u-", "sin", "cos", "tan" };
	const int init_input_priority[] = { 3, 3, 5, 5, 2, 8, 9, 10, 10, 10 };
	const int init_stack_priority[] = { 4, 4, 6, 6, 1, 7, 8, 9, 9, 9 };
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

std::string FormatInfix(const std::string& infix)
{
	std::string::const_iterator bos = infix.begin();
	std::string::const_iterator eos = infix.end();
	std::string formatted;

	for (std::string::const_iterator it = bos; it != eos; ++it)
	{
		if (std::find(operators.begin(), operators.end(), std::string(1, *it)) != operators.end() || *it == '(' || *it == ')')
		{
			if (it != bos && *(it - 1) != ' ' && *(formatted.end() - 1) != ' ' )
			{
				formatted.append(1, ' ');
			}

			formatted.append(1, *it);

			if ((it + 1) != eos && *(it + 1) != ' ')
			{
				formatted.append(1, ' ');
			}
		}
		else 
		{
			if (*it != ' ')
			{
				formatted.append(1, *it);
			}
			else if (it != bos && *(it - 1) != ' ')
			{
				formatted.append(1, *it);
			}
		}
	}

	return formatted;
}

std::string InfixToPostfix(const std::string& infix)
{
	std::stack<std::string> operatorStack;
	std::string token;
	std::string previousToken = "";
	int parenCount = 0;
	bool isUnary = true;

	std::istringstream is(FormatInfix(infix));
	std::string postfix;

	while (is >> token)
	{
		if (std::find(operators.begin(), operators.end(), token) != operators.end())
		{
			if (previousToken == "(")
			{
				throw InfixError("Operator can't evaluate with invalid operands");
			}

			if (isUnary && token == "-")
			{
				token = "u" + token;
			}
			else
			{
				while (!operatorStack.empty() && input_priority.find(token)->second <= stack_priority.find(operatorStack.top())->second)
				{
					postfix += operatorStack.top() + ' ';
					operatorStack.pop();
				}
			}

			operatorStack.push(token);
			isUnary = true;
		}
		else if (token == "(")
		{
			operatorStack.push(token);
			++parenCount;
		}
		else if (token == ")")
		{
			if (parenCount == 0)
			{
				throw InfixError("Invalid Paren");
			}
			if (previousToken == "(" && !postfix.empty())
			{
				throw InfixError("Invalid Paren");
			}
			
			while (!operatorStack.empty() && operatorStack.top() != "(")
			{
				postfix += operatorStack.top() + ' ';
				operatorStack.pop();
			}

			operatorStack.pop();
			--parenCount;
		}
		else if (token.find_first_not_of(operand_chars) == std::string::npos)
		{
			if (previousToken == ")")
			{
				throw InfixError("Operator can't evaluate with invalid operands");
			}

			postfix += token + ' ';
			isUnary = false;
		}
		else
		{
			throw InfixError("Undefined Symbol");
		}

		previousToken = token;
	}

	if (parenCount > 0)
	{
		throw InfixError("Invalid Paren");
	}

	while (!operatorStack.empty())
	{
		postfix += operatorStack.top() + ' ';
		operatorStack.pop();
	}

	if (!postfix.empty())
	{
		postfix.erase(postfix.size() - 1);
	}

	size_t equalPos = infix.find("=");

	if (equalPos != std::string::npos)
	{
		if (infix.substr(0, equalPos).find_first_not_of(identifier_chars + " " + "\t") != std::string::npos)
		{
			throw InfixError("Invalid Variable");
		}
		if (equalPos != infix.rfind("="))
		{
			throw InfixError("Invalid Variable");
		}
	}

	return postfix;
}