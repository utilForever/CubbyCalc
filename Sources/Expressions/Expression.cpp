#include <Expressions/Expression.hpp>
#include <Operators/Assign.hpp>
#include <Operators/BinaryOperator.hpp>

#include <string>

Expression::Expression(ExpressionTree* expTree)
	: m_topNode(expTree)
{ }

Expression::~Expression()
{
	if (m_topNode != nullptr)
	{
		delete m_topNode;
		m_topNode = nullptr;
	}
}

Expression::Expression(const Expression& exp)
	: m_topNode(nullptr)
{
	if (!exp.Empty())
	{
		m_topNode = exp.m_topNode->Clone();
	}
}

Expression& Expression::operator=(Expression& exp)
{
	if (this != &exp)
	{
		Expression temp(exp);
		Swap(temp);
	}

	return *this;
}

Expression& Expression::operator=(ExpressionTree* expTree)
{
	Expression temp(expTree);
	Swap(temp);

	return *this;
}

double Expression::Evaluate() const
{
	if (Empty())
	{
		throw ExpressionError("Error: Expression is empty!");
	}

	return m_topNode->Evaluate();
}

void Expression::PrintTree(std::ostream& os) const
{
	if (Empty())
	{
		throw ExpressionError("Error: Expression is empty!");
	}

	m_topNode->Print(os);
}

std::string Expression::GetPostfix() const
{
	return Empty() ? "" : m_topNode->GetPostfix();
}

std::string Expression::GetInfix() const
{
	return Empty() ? "" : m_topNode->GetInfix(true);
}

void Expression::Swap(Expression& exp)
{
	if (this != &exp)
	{
		std::swap(m_topNode, exp.m_topNode);
	}
}

bool Expression::Empty() const
{
	return !m_topNode;
}

bool Expression::TopNodeIsAssign() const
{
	return dynamic_cast<Assign*>(m_topNode);
}