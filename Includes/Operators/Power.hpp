#ifndef CUBBYCALC_POWER_HPP
#define CUBBYCALC_POWER_HPP

#include <Operators/BinaryOperator.hpp>

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

#endif