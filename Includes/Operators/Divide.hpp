#ifndef CUBBYCALC_DIVIDE_HPP
#define CUBBYCALC_DIVIDE_HPP

#include <Operators/BinaryOperator.hpp>

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

#endif