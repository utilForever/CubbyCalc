#include <Operands/Integer.hpp>

#include <iomanip>
#include <sstream>

Integer::Integer(int value)
	: m_value(value)
{ }

Integer::Integer(const Integer& integerNode)
	: Operand(integerNode), m_value(integerNode.m_value)
{ }

std::string Integer::ToString() const
{
	std::ostringstream oss;
	oss << m_value;
	return oss.str();
}

ExpressionTree* Integer::Clone() const
{
	return new Integer(*this);
}

double Integer::Evaluate() const
{
	return m_value;
}