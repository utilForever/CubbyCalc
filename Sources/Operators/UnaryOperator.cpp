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