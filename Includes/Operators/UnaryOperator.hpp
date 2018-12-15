#ifndef CUBBYCALC_UNARY_OPERATOR_HPP
#define CUBBYCALC_UNARY_OPERATOR_HPP

#include <Expressions/ExpressionTree.hpp>

#include <string>

class UnaryOperator : public ExpressionTree
{
private:
	UnaryOperator& operator=(const UnaryOperator&);

protected:
	UnaryOperator(ExpressionTree*);
	UnaryOperator(const UnaryOperator&);

	ExpressionTree* m_tree;

public:
	~UnaryOperator();

	virtual double Evaluate() const = 0;
	virtual ExpressionTree* Clone() const = 0;
	virtual std::string GetPostfix() const;
	virtual void Print(std::ostream&, int = 0) const;
	virtual std::string GetInfix(bool = false) const;
};

#endif