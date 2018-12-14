#include <Operands/Real.hpp>

#include <iomanip>
#include <sstream>

Real::Real(double value)
	: m_value(value)
{ }

Real::Real(const Real& realNode)
	: Operand(realNode), m_value(realNode.m_value)
{ }

std::string Real::ToString() const
{
	std::ostringstream oss;
	oss << m_value;
	return oss.str();
}

double Real::Evaluate() const
{
	return m_value;
}

ExpressionTree* Real::Clone() const
{
	return new Real(*this);
}