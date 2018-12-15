#include <Expressions/ExpressionTree.hpp>
#include <Operands/Variable.hpp>
#include <Operators/BinaryOperator.hpp>

#include <cmath>
#include <iomanip>

BinaryOperator::BinaryOperator(ExpressionTree* left, ExpressionTree* right)
	: m_leftTree(left), m_rightTree(right)
{
	if (!(left && right))
	{
		delete m_leftTree;
		delete m_rightTree;
		throw ExpressionTreeError("Operator can't operate");
	}
}

BinaryOperator::BinaryOperator(const BinaryOperator& operatorNode)
	: ExpressionTree(operatorNode), m_leftTree(operatorNode.m_leftTree->Clone()), m_rightTree(operatorNode.m_rightTree->Clone())
{ }

BinaryOperator::~BinaryOperator()
{
	delete m_leftTree;
	delete m_rightTree;
}

std::string BinaryOperator::GetPostfix() const
{
	return (m_leftTree->GetPostfix() + m_rightTree->GetPostfix() + ToString() + " ");
}

std::string BinaryOperator::GetInfix(bool isFirst) const
{
	return ((isFirst) ? "" : "(") +
		m_leftTree->GetInfix() + " " + ToString() + " " + m_rightTree->GetInfix() +
		((isFirst) ? "" : ")");
}

void BinaryOperator::Print(std::ostream& os, int depth) const
{
	m_rightTree->Print(os, depth + 3);

	os << std::setw(depth + 2) << "/" << std::endl
		<< std::setw(depth) << ToString() << std::endl
		<< std::setw(depth + 2) << "\\" << std::endl;

	m_leftTree->Print(os, depth + 3);
}