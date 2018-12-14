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

Plus::Plus(ExpressionTree* left, ExpressionTree* right)
	: BinaryOperator(left, right)
{ }

Plus::Plus(const Plus& plusNode)
	: BinaryOperator(plusNode)
{ }

ExpressionTree* Plus::Clone() const
{
	return new Plus(*this);
}

std::string Plus::ToString() const
{
	return "+";
}

double Plus::Evaluate() const
{
	return m_leftTree->Evaluate() + m_rightTree->Evaluate();
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

Multiply::Multiply(ExpressionTree* left, ExpressionTree* right)
	: BinaryOperator(left, right)
{ }

Multiply::Multiply(const Multiply& multiplyNode)
	: BinaryOperator(multiplyNode)
{ }

ExpressionTree* Multiply::Clone() const
{
	return new Multiply(*this);
}

std::string Multiply::ToString() const
{
	return "*";
}

double Multiply::Evaluate() const
{
	return m_leftTree->Evaluate() * m_rightTree->Evaluate();
}

Divide::Divide(ExpressionTree* left, ExpressionTree* right)
	: BinaryOperator(left, right)
{ }

Divide::Divide(const Divide& divideNode)
	: BinaryOperator(divideNode)
{ }

ExpressionTree* Divide::Clone() const
{
	return new Divide(*this);
}

std::string Divide::ToString() const
{
	return "/";
}

double Divide::Evaluate() const
{
	double tempEval = m_rightTree->Evaluate();

	if (tempEval == 0)
	{
		throw ExpressionTreeError("Divided by 0");
	}

	return m_leftTree->Evaluate() / tempEval;
}

Power::Power(ExpressionTree* left, ExpressionTree* right)
	: BinaryOperator(left, right)
{ }

Power::Power(const Power& powerNode)
	: BinaryOperator(powerNode)
{ }

ExpressionTree* Power::Clone() const
{
	return new Power(*this);
}

std::string Power::ToString() const
{
	return "^";
}

double Power::Evaluate() const
{
	return std::pow(m_leftTree->Evaluate(), m_rightTree->Evaluate());
}

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