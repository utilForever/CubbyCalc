#ifndef UNARY_OPERATOR_H
#define UNARY_OPERATOR_H

#include <Expressions/ExpressionTree.hpp>

#include <string>

class UnaryOperator : public ExpressionTree
{
private:
	UnaryOperator& operator=(const UnaryOperator&);

protected:
	UnaryOperator(ExpressionTree*);
	UnaryOperator(const UnaryOperator&);

	ExpressionTree* m_tree;

public:
	~UnaryOperator();

	virtual double Evaluate() const = 0;
	virtual ExpressionTree* Clone() const = 0;
	virtual std::string GetPostfix() const;
	virtual void Print(std::ostream&, int = 0) const;
	virtual std::string GetInfix(bool = false) const;
};

class UnaryMinus : public UnaryOperator
{
protected:
	UnaryMinus(const UnaryMinus&);

public:
	UnaryMinus(ExpressionTree* = 0);

	ExpressionTree* Clone() const;
	std::string ToString() const;
	double Evaluate() const;
};

class Sine : public UnaryOperator
{
protected:
	Sine(const Sine&);

public:
	Sine(ExpressionTree* = 0);

	ExpressionTree* Clone() const;
	std::string ToString() const;
	double Evaluate() const;
};

class Cosine : public UnaryOperator
{
protected:
	Cosine(const Cosine&);

public:
	Cosine(ExpressionTree* = 0);

	ExpressionTree* Clone() const;
	std::string ToString() const;
	double Evaluate() const;
};

class Tangent : public UnaryOperator
{
protected:
	Tangent(const Tangent&);

public:
	Tangent(ExpressionTree* = 0);

	ExpressionTree* Clone() const;
	std::string ToString() const;
	double Evaluate() const;
};

#endif