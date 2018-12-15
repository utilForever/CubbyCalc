#include <Operators/Minus.hpp>

UnaryMinus::UnaryMinus(ExpressionTree* child)
	: UnaryOperator(child)
{ }

UnaryMinus::UnaryMinus(const UnaryMinus& minusNode)
	: UnaryOperator(minusNode)
{ }

ExpressionTree* UnaryMinus::Clone() const
{
	return new UnaryMinus(*this);
}

std::string UnaryMinus::ToString() const
{
	return "-";
}

double UnaryMinus::Evaluate() const
{
	return -1 * m_tree->Evaluate();
}

BinaryMinus::BinaryMinus(ExpressionTree* left, ExpressionTree* right)
	: BinaryOperator(left, right)
{ }

BinaryMinus::BinaryMinus(const BinaryMinus& minusNode)
	: BinaryOperator(minusNode)
{ }

ExpressionTree* BinaryMinus::Clone() const
{
	return new BinaryMinus(*this);
}

std::string BinaryMinus::ToString() const
{
	return "-";
}

double BinaryMinus::Evaluate() const
{
	return m_leftTree->Evaluate() - m_rightTree->Evaluate();
}