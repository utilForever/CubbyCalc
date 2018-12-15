#include <Operators/Cosine.hpp>

#include <cmath>

Cosine::Cosine(ExpressionTree* child)
	: UnaryOperator(child)
{ }

Cosine::Cosine(const Cosine& cosineNode)
	: UnaryOperator(cosineNode)
{ }

ExpressionTree* Cosine::Clone() const
{
	return new Cosine(*this);
}

std::string Cosine::ToString() const
{
	return "cos";
}

double Cosine::Evaluate() const
{
	return std::cos(m_tree->Evaluate());
}