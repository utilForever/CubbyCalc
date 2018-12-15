#include <Expressions/ExpressionMaker.hpp>
#include <Expressions/ExpressionUtil.hpp>
#include <Programs/Calculator.hpp>

#include <iostream>
#include <sstream>
#include <string>
#include <regex>

const std::string Calculator::m_validCommand("?REPITVQ");
const std::string Calculator::m_numberedCommand("EPIT");

Calculator::Calculator()
	: m_expMaker(ExpressionMaker(m_varTable))
{ }

Calculator::~Calculator()
{ }

void Calculator::Run()
{
	std::cout << "Calculator Version 1.03" << std::endl;
	PrintHelp();

	for (;;)
	{
		try 
		{
			do 
			{
				GetCommand();
				if (ValidCommand())
				{
					ExecuteCommand();
				}
			}
			while (m_command != 'Q');

			break;
		}
		catch (const std::exception& e)
		{
			std::cout << e.what() << std::endl;
		}
	}
}

void Calculator::PrintHelp()
{
	std::cout
		<< "?  : Help" << std::endl
		<< "R  : Read expression" << std::endl
		<< "E  : Evaluate and print latest expression" << std::endl
		<< "E n: Evaluate and print nth expression" << std::endl
		<< "P  : Print latest expression postfix" << std::endl
		<< "P n: Print nth expression postfix" << std::endl
		<< "I  : Print latest expression infix" << std::endl
		<< "I n: Print nth expression infix" << std::endl
		<< "T  : Print latest expression tree" << std::endl
		<< "T n: Print nth expression tree" << std::endl
		<< "V  : Print variable table list" << std::endl
		<< "Q  : Quit" << std::endl;
}

void Calculator::GetCommand()
{
	std::cout << ">> ";
	std::string readString = "";
	getline(std::cin, readString);
	std::istringstream iss(readString);

	iss >> std::ws;
	iss >> m_command;
	m_command = static_cast<char>(toupper(static_cast<int>(m_command)));

	if (m_numberedCommand.find(m_command) != std::string::npos)
	{
		size_t readNumber = m_oldExpressions.size();
		iss >> std::ws;
		if (isdigit(iss.peek()))
		{
			iss >> readNumber;
			if (readNumber < 1 || readNumber > m_oldExpressions.size())
			{
				m_expressionNumber = m_oldExpressions.size() - 1;
				throw std::logic_error("The number is out of range");
			}

			m_expressionNumber = readNumber - 1;
		}
		else
		{
			m_expressionNumber = std::numeric_limits<unsigned int>::max();
		}
	}
}

bool Calculator::ValidCommand()
{
	if (m_validCommand.find(m_command) == std::string::npos)
	{
		std::cout << "Invalid Command: " << m_command << std::endl;
		return false;
	}

	return true;
}

void Calculator::ExecuteCommand()
{
	if (m_command == '?')
	{
		PrintHelp();
	}
	else if (m_command == 'R')
	{
		ReadExpression(std::cin);
	}
	else if (m_command == 'E')
	{
		EvaluateAndPrintExpression(std::cout);
	}
	else if (m_command == 'P')
	{
		PrintPostfix(std::cout);
	}
	else if (m_command == 'I')
	{
		PrintInfix(std::cout);
	}
	else if (m_command == 'T')
	{
		PrintTree(std::cout);
	}
	else if (m_command == 'V')
	{
		m_varTable.List(std::cout);
	}
	else if (m_command == 'Q')
	{
		std::cout << "Quit!" << std::endl;
	}
	else
	{
		std::cout << "Invalid Command" << std::endl;
	}
}

void Calculator::ReadExpression(std::istream& is)
{
	std::string infix;
	
	is >> std::ws;

	if (getline(is, infix))
	{
		std::vector<std::string> expressions = SplitExpression(infix, ",");

		for (auto& expression : expressions)
		{
			m_expMaker.SetPostfix(InfixToPostfix(expression));
			Expression exp = m_expMaker.GetExpression();
			m_oldExpressions.push_back(Expression(exp));
			m_currentExpression = exp;

			if (m_currentExpression.TopNodeIsAssign())
			{
				m_currentExpression.Evaluate();
			}
		}
	}
	else
	{
		std::cout << "Invalid Expression" << std::endl;
	}
}

void Calculator::PrintExpression(std::ostream& os) const
{
	std::vector<Expression>::const_iterator iter = m_oldExpressions.begin();

	for (int i = 1; iter != m_oldExpressions.end(); ++iter, ++i)
	{
		os << i << ": " << (*iter).GetInfix() << std::endl;
	}
}

void Calculator::EvaluateAndPrintExpression(std::ostream& os) const
{
	if (m_expressionNumber == std::numeric_limits<unsigned int>::max())
	{
		os << m_currentExpression.Evaluate() << std::endl;
	}
	else
	{
		os << m_oldExpressions.at(m_expressionNumber).Evaluate() << std::endl;
	}
}

void Calculator::PrintPostfix(std::ostream& os) const
{
	if (m_expressionNumber == std::numeric_limits<unsigned int>::max())
	{
		os << m_currentExpression.GetPostfix() << std::endl;
	}
	else
	{
		os << m_oldExpressions.at(m_expressionNumber).GetPostfix() << std::endl;
	}
}

void Calculator::PrintInfix(std::ostream& os) const
{
	if (m_expressionNumber == std::numeric_limits<unsigned int>::max())
	{
		os << m_currentExpression.GetInfix() << std::endl;
	}
	else
	{
		os << m_oldExpressions.at(m_expressionNumber).GetInfix() << std::endl;
	}
}

void Calculator::PrintTree(std::ostream& os) const
{
	if (m_expressionNumber == std::numeric_limits<unsigned int>::max())
	{
		m_currentExpression.PrintTree(os);
	}
	else
	{
		m_oldExpressions.at(m_expressionNumber).PrintTree(os);
	}
}

void Calculator::SetCurrentExpression()
{
	if (m_expressionNumber == std::numeric_limits<unsigned int>::max())
	{
		throw std::logic_error("Too many expressions");
	}
	else
	{
		Expression exp = m_oldExpressions[m_expressionNumber];
		m_currentExpression = exp;
	}
}

std::vector<std::string> Calculator::SplitExpression(const std::string& input, const std::string& regex)
{
	// passing -1 as the submatch index parameter performs splitting
	std::regex re(regex);
	std::sregex_token_iterator first{ input.begin(), input.end(), re, -1 }, last;

	return { first, last };
}