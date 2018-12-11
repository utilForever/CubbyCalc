#include <Operand.hpp>

#include <iomanip>
#include <sstream>

Operand::Operand()
{ }

Operand::Operand(const Operand& operandNode)
	: ExpressionTree(operandNode)
{ }

std::string Operand::GetPostfix() const
{
	return (ToString() + " ");
}

std::string Operand::GetInfix(bool) const
{
	return ToString();
}

void Operand::Print(std::ostream& os, int depth) const
{
	os << std::setw(depth) << ToString() << std::endl;
}

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

Variable::Variable(const std::string& token, VariableTable& varTable)
	: m_token(token), m_varTable(varTable)
{ }

Variable::Variable(const Variable& variableNode)
	: Operand(variableNode), m_token(variableNode.m_token), m_varTable(variableNode.m_varTable)
{ }

double Variable::Evaluate() const
{
	return GetValue();
}

ExpressionTree* Variable::Clone() const
{
	return new Variable(*this);
}

double Variable::GetValue() const
{
	return m_varTable.GetValue(m_token);
}

void Variable::SetValue(const double& value)
{
	m_varTable.SetValue(m_token, value);
}

std::string Variable::ToString() const
{
	return m_token;
}
