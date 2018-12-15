#include <Operands/Variable.hpp>
#include <Operators/Assign.hpp>

Assign::Assign(ExpressionTree* left, ExpressionTree* right, VariableTable& varTable)
	: BinaryOperator(left, right), m_varTable(varTable)
{ }

Assign::Assign(const Assign& assignNode)
	: BinaryOperator(assignNode), m_varTable(assignNode.m_varTable)
{ }

ExpressionTree* Assign::Clone() const
{
	return new Assign(*this);
}

std::string Assign::ToString() const
{
	return "=";
}

std::string Assign::GetInfix(bool) const
{
	return m_leftTree->GetInfix(true) + " " + ToString() + " " + m_rightTree->GetInfix(true);
}

double Assign::Evaluate() const
{
	double rightTreeValue = m_rightTree->Evaluate();
	Variable* varPointer = dynamic_cast<Variable*>(m_leftTree);

	if (varPointer)
	{
		if (m_varTable.Find(varPointer->ToString()))
		{
			varPointer->SetValue(rightTreeValue);
		}
		else
		{
			m_varTable.Insert(varPointer->ToString(), rightTreeValue);
		}
	}
	else
	{
		throw ExpressionTreeError("Invalid Assign");
	}

	return rightTreeValue;
}