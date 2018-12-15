#include <Commons/Constants.hpp>
#include <Expressions/ExpressionUtil.hpp>

#include <algorithm>
#include <sstream>
#include <stack>
#include <vector>

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
		// sin, cos, tan
		else if (infix.size() > 3 && it < eos - 3 && std::find(operators.begin(), operators.end(), std::string(it, it + 3)) != operators.end())
		{
			if (it != bos && *(it - 1) != ' ' && *(formatted.end() - 1) != ' ')
			{
				formatted.append(1, ' ');
			}

			formatted.append(it, it + 3);
			it += 2;

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
		if (token != "(" && std::find(operators.begin(), operators.end(), token) != operators.end())
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
