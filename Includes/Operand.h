#ifndef OPERAND_H
#define OPERAND_H

#include <string>

#include "VariableTable.h"
#include "ExpressionTree.h"

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