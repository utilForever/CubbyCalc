#include <Operators/Power.hpp>

#include <cmath>

Power::Power(ExpressionTree* left, ExpressionTree* right)
	: BinaryOperator(left, right)
{ }

Power::Power(const Power& powerNode)
	: BinaryOperator(powerNode)
{ }

ExpressionTree* Power::Clone() const
{
	return new Power(*this);
}

std::string Power::ToString() const
{
	return "^";
}

double Power::Evaluate() const
{
	return std::pow(m_leftTree->Evaluate(), m_rightTree->Evaluate());
}