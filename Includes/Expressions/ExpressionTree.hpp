#ifndef CUBBYCALC_EXPRESSION_TREE_HPP
#define CUBBYCALC_EXPRESSION_TREE_HPP

#include <stdexcept>

class ExpressionTreeError : public std::logic_error
{
public:
	explicit ExpressionTreeError(const std::string& whatArg) throw()
		: logic_error(whatArg) { }
};

class ExpressionTree
{
private:
	ExpressionTree& operator=(const ExpressionTree&);
	
protected:
	ExpressionTree(const ExpressionTree&);
public:
	ExpressionTree();
	virtual ~ExpressionTree();

	virtual double Evaluate() const = 0;
	virtual std::string GetPostfix() const = 0;
	virtual std::string ToString() const = 0;
	virtual void Print(std::ostream&, int = 0) const = 0;
	virtual ExpressionTree* Clone() const = 0;
	virtual std::string GetInfix(bool = false) const = 0;
};

#endif