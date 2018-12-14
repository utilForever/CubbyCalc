#ifndef CUBBYCALC_VARIABLE_HPP
#define CUBBYCALC_VARIABLE_HPP

#include <Operands/Operand.hpp>

class Variable : public Operand
{
private:
	std::string m_token;
	VariableTable& m_varTable;

protected:
	Variable(const Variable&);

public:
	Variable(const std::string&, VariableTable&);

	double GetValue() const;
	void SetValue(const double&);

	ExpressionTree* Clone() const;
	std::string ToString() const;
	double Evaluate() const;
};

#endif