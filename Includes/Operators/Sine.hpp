#ifndef CUBBYCALC_SINE_HPP
#define CUBBYCALC_SINE_HPP

#include <Operators/UnaryOperator.hpp>

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

#endif