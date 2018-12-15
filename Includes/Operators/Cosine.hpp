#ifndef CUBBYCALC_COSINE_HPP
#define CUBBYCALC_COSINE_HPP

#include <Operators/UnaryOperator.hpp>

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

#endif