#ifndef CUBBYCALC_MINUS_HPP
#define CUBBYCALC_MINUS_HPP

#include <Operators/BinaryOperator.hpp>
#include <Operators/UnaryOperator.hpp>

class UnaryMinus : public UnaryOperator
{
protected:
	UnaryMinus(const UnaryMinus&);

public:
	UnaryMinus(ExpressionTree* = 0);

	ExpressionTree* Clone() const;
	std::string ToString() const;
	double Evaluate() const;
};

class BinaryMinus : public BinaryOperator
{
protected:
	BinaryMinus(const BinaryMinus&);

public:
	BinaryMinus(ExpressionTree* = 0, ExpressionTree* = 0);

	ExpressionTree* Clone() const;
	std::string ToString() const;
	double Evaluate() const;
};


#endif