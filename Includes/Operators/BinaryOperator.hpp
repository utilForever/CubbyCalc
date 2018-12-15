#ifndef CUBBYCALC_BINARY_OPERATOR_HPP
#define CUBBYCALC_BINARY_OPERATOR_HPP

#include <Expressions/ExpressionTree.hpp>
#include <Variables/VariableTable.hpp>

class BinaryOperator : public ExpressionTree
{
private:
	BinaryOperator& operator=(const BinaryOperator&);

protected:
	BinaryOperator(ExpressionTree*, ExpressionTree*);
	BinaryOperator(const BinaryOperator&);

	ExpressionTree* m_leftTree;
	ExpressionTree* m_rightTree;

public:
	~BinaryOperator();

	virtual double Evaluate() const = 0;
	virtual ExpressionTree* Clone() const = 0;
	virtual std::string GetPostfix() const;
	virtual void Print(std::ostream&, int = 0) const;
	virtual std::string GetInfix(bool = false) const;
};

class Multiply : public BinaryOperator
{
protected:
	Multiply(const Multiply&);

public:
	Multiply(ExpressionTree* = 0, ExpressionTree* = 0);

	ExpressionTree* Clone() const;
	std::string ToString() const;
	double Evaluate() const;
};

class Divide : public BinaryOperator
{
protected:
	Divide(const Divide&);

public:
	Divide(ExpressionTree* = 0, ExpressionTree* = 0);

	ExpressionTree* Clone() const;
	std::string ToString() const;
	double Evaluate() const;
};

class Power : public BinaryOperator
{
protected:
	Power(const Power&);

public:
	Power(ExpressionTree* = 0, ExpressionTree* = 0);

	ExpressionTree* Clone() const;
	std::string ToString() const;
	double Evaluate() const;
};

class Assign : public BinaryOperator
{
private:
	VariableTable& m_varTable;

protected:
	Assign(const Assign&);

public:
	Assign(ExpressionTree*, ExpressionTree*, VariableTable&);

	ExpressionTree* Clone() const;
	std::string ToString() const;
	double Evaluate() const;
	virtual std::string GetInfix(bool = false) const;
};

#endif