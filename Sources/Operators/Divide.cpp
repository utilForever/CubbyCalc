#include <Operators/Divide.hpp>

Divide::Divide(ExpressionTree* left, ExpressionTree* right)
	: BinaryOperator(left, right)
{ }

Divide::Divide(const Divide& divideNode)
	: BinaryOperator(divideNode)
{ }

ExpressionTree* Divide::Clone() const
{
	return new Divide(*this);
}

std::string Divide::ToString() const
{
	return "/";
}

double Divide::Evaluate() const
{
	double tempEval = m_rightTree->Evaluate();

	if (tempEval == 0)
	{
		throw ExpressionTreeError("Divided by 0");
	}

	return m_leftTree->Evaluate() / tempEval;
}