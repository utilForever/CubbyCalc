#ifndef CUBBYCALC_INTEGER_HPP
#define CUBBYCALC_INTEGER_HPP

#include <Operands/Operand.hpp>

class Integer : public Operand
{
private:
	int m_value;

protected:
	Integer(const Integer&);

public:
	Integer(int = 0);

	ExpressionTree* Clone() const;
	std::string ToString() const;
	double Evaluate() const;
};

#endif