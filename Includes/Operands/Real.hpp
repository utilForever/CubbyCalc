#ifndef CUBBYCALC_REAL_HPP
#define CUBBYCALC_REAL_HPP

#include <Operands/Operand.hpp>

class Real : public Operand
{
private:
	double m_value;

protected:
	Real(const Real&);

public:
	Real(double = 0.0);

	ExpressionTree* Clone() const;
	std::string ToString() const;
	double Evaluate() const;
};

#endif