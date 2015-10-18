#ifndef EXPRESSION_H
#define EXPRESSION_H

#include <stdexcept>

#include "ExpressionTree.h"

class ExpressionError : public std::logic_error
{
public:
	explicit ExpressionError(const std::string& whatArg) throw()
		: logic_error(whatArg) { }
};

class Expression
{
private:
	ExpressionTree* m_topNode;
public:
	friend class Calculator;
	
	Expression(ExpressionTree* = 0);
	~Expression();

	Expression(const Expression&);
	
	Expression& operator=(Expression&);
	Expression& operator=(ExpressionTree*);

	double Evaluate() const;
	void PrintTree(std::ostream&) const;
	std::string GetPostfix() const;
	std::string GetInfix() const;
	void Swap(Expression&);
	bool Empty() const;
};

#endif