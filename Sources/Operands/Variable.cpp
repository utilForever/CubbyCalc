#include <Operands/Operand.hpp>
#include <Operands/Variable.hpp>
#include <Variables/VariableTable.hpp>

#include <iomanip>
#include <sstream>

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