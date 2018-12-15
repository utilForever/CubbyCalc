#include <Operators/UnaryOperator.hpp>

#include <cmath>
#include <iomanip>

UnaryOperator::UnaryOperator(ExpressionTree* child)
	: m_tree(child)
{
	if (!child)
	{
		delete m_tree;

		throw ExpressionTreeError("Operator can't operate");
	}
}

UnaryOperator::UnaryOperator(const UnaryOperator& operatorNode)
	: ExpressionTree(operatorNode), m_tree(operatorNode.m_tree->Clone())
{ }

UnaryOperator::~UnaryOperator()
{
	delete m_tree;
}

std::string UnaryOperator::GetPostfix() const
{
	return (m_tree->GetPostfix() + ToString() + " ");
}

std::string UnaryOperator::GetInfix(bool isFirst) const
{
	return ((isFirst) ? "" : "(") +
		ToString() + m_tree->GetInfix() + " " +
		((isFirst) ? "" : ")");
}

void UnaryOperator::Print(std::ostream& os, int depth) const
{
	m_tree->Print(os, depth + 3);

	os << std::setw(depth + 2) << "/" << std::endl
		<< std::setw(depth) << ToString() << std::endl
		<< std::setw(depth + 2) << "\\" << std::endl;
}