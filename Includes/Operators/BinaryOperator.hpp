#ifndef CUBBYCALC_BINARY_OPERATOR_HPP
#define CUBBYCALC_BINARY_OPERATOR_HPP

#include <Expressions/ExpressionTree.hpp>
#include <Variables/VariableTable.hpp>

class BinaryOperator : public ExpressionTree
{
private:
	BinaryOperator& operator=(const BinaryOperator&);

protected:
	BinaryOperator(ExpressionTree*, ExpressionTree*);
	BinaryOperator(const BinaryOperator&);

	ExpressionTree* m_leftTree;
	ExpressionTree* m_rightTree;

public:
	~BinaryOperator();

	virtual double Evaluate() const = 0;
	virtual ExpressionTree* Clone() const = 0;
	virtual std::string GetPostfix() const;
	virtual void Print(std::ostream&, int = 0) const;
	virtual std::string GetInfix(bool = false) const;
};

#endif