#include <Operators/Tangent.hpp>

#include <cmath>

Tangent::Tangent(ExpressionTree* child)
	: UnaryOperator(child)
{ }

Tangent::Tangent(const Tangent& tangentNode)
	: UnaryOperator(tangentNode)
{ }

ExpressionTree* Tangent::Clone() const
{
	return new Tangent(*this);
}

std::string Tangent::ToString() const
{
	return "tan";
}

double Tangent::Evaluate() const
{
	return std::tan(m_tree->Evaluate());
}