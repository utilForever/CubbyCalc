#include <Operators/Plus.hpp>

Plus::Plus(ExpressionTree* left, ExpressionTree* right)
	: BinaryOperator(left, right)
{ }

Plus::Plus(const Plus& plusNode)
	: BinaryOperator(plusNode)
{ }

ExpressionTree* Plus::Clone() const
{
	return new Plus(*this);
}

std::string Plus::ToString() const
{
	return "+";
}

double Plus::Evaluate() const
{
	return m_leftTree->Evaluate() + m_rightTree->Evaluate();
}