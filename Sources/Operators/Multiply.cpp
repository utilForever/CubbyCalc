#include <Operators/Multiply.hpp>

Multiply::Multiply(ExpressionTree* left, ExpressionTree* right)
	: BinaryOperator(left, right)
{ }

Multiply::Multiply(const Multiply& multiplyNode)
	: BinaryOperator(multiplyNode)
{ }

ExpressionTree* Multiply::Clone() const
{
	return new Multiply(*this);
}

std::string Multiply::ToString() const
{
	return "*";
}

double Multiply::Evaluate() const
{
	return m_leftTree->Evaluate() * m_rightTree->Evaluate();
}