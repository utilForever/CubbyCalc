#include <Operators/Sine.hpp>

#include <cmath>

Sine::Sine(ExpressionTree* child)
	: UnaryOperator(child)
{ }

Sine::Sine(const Sine& sineNode)
	: UnaryOperator(sineNode)
{ }

ExpressionTree* Sine::Clone() const
{
	return new Sine(*this);
}

std::string Sine::ToString() const
{
	return "sin";
}

double Sine::Evaluate() const
{
	return std::sin(m_tree->Evaluate());
}