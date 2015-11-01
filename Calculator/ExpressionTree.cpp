#include <sstream>
#include <iomanip>

#include "ExpressionTree.h"

ExpressionTree::ExpressionTree()
{ }

ExpressionTree::ExpressionTree(const ExpressionTree&)
{ }

ExpressionTree::~ExpressionTree()
{ }

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
	return pow(m_leftTree->Evaluate(), m_rightTree->Evaluate());
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
