#ifndef EXPRESSION_TREE_H
#define EXPRESSION_TREE_H

#include <stdexcept>

#include "VariableTable.h"

class ExpressionTreeError : public std::logic_error
{
public:
	explicit ExpressionTreeError(const std::string& whatArg) throw()
		: logic_error(whatArg) { }
};

class ExpressionTree
{
private:
	ExpressionTree& operator=(const ExpressionTree&);
	
protected:
	ExpressionTree(const ExpressionTree&);
public:
	ExpressionTree();
	virtual ~ExpressionTree();

	virtual double Evaluate() const = 0;
	virtual std::string GetPostfix() const = 0;
	virtual std::string ToString() const = 0;
	virtual void Print(std::ostream&, int = 0) const = 0;
	virtual ExpressionTree* Clone() const = 0;
	virtual std::string GetInfix(bool = false) const = 0;
};

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

class Operand : public ExpressionTree
{
protected:
	Operand(const Operand&);

public:
	Operand();

	virtual double Evaluate() const = 0;
	virtual ExpressionTree* Clone() const = 0;
	virtual std::string ToString() const = 0;
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

class Plus : public BinaryOperator
{
protected:
	Plus(const Plus&);

public:
	Plus(ExpressionTree*, ExpressionTree*);
	
	ExpressionTree* Clone() const;
	std::string ToString() const;
	double Evaluate() const;
};

class BinaryMinus : public BinaryOperator
{
protected:
	BinaryMinus(const BinaryMinus&);

public:
	BinaryMinus(ExpressionTree* = 0, ExpressionTree* = 0);

	ExpressionTree* Clone() const;
	std::string ToString() const;
	double Evaluate() const;
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

class Integer : public Operand
{
private:
	int m_value;

protected:
	Integer(const Integer&);

public:
	Integer(int = 0);

	ExpressionTree* Clone() const;
	std::string ToString() const;
	double Evaluate() const;
};

class Real : public Operand
{
private:
	double m_value;

protected:
	Real(const Real&);

public:
	Real(double = 0.0);

	ExpressionTree* Clone() const;
	std::string ToString() const;
	double Evaluate() const;
};

class Variable : public Operand
{
private:
	std::string m_token;
	VariableTable& m_varTable;

protected:
	Variable(const Variable&);

public:
	Variable(const std::string&, VariableTable&);

	double GetValue() const;
	void SetValue(const double&);

	ExpressionTree* Clone() const;
	std::string ToString() const;
	double Evaluate() const;

};

#endif