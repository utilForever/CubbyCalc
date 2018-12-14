#ifndef CUBBYCALC_OPERAND_HPP
#define CUBBYCALC_OPERAND_HPP

#include <Expressions/ExpressionTree.hpp>
#include <Variables/VariableTable.hpp>

#include <string>

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

#endif