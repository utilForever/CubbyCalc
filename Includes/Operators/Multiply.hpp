#ifndef CUBBYCALC_MULTIPLY_HPP
#define CUBBYCALC_MULTIPLY_HPP

#include <Operators/BinaryOperator.hpp>

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

#endif