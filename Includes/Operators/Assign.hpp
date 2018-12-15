#ifndef CUBBYCALC_ASSIGN_HPP
#define CUBBYCALC_ASSIGN_HPP

#include <Operators/BinaryOperator.hpp>

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