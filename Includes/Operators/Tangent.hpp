#ifndef CUBBYCALC_TANGENT_HPP
#define CUBBYCALC_TANGENT_HPP

#include <Operators/UnaryOperator.hpp>

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