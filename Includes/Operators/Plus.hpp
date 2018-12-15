#ifndef CUBBYCALC_PLUS_HPP
#define CUBBYCALC_PLUS_HPP

#include <Operators/BinaryOperator.hpp>

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

#endif