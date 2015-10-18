#ifndef EXPRESSION_TREE_H
#define EXPRESSION_TREE_H

#include <stdexcept>

class ExpressionTreeError : public std::logic_error
{
public:
	explicit ExpressionTreeError(const std::string& whatArg) throw()
		: logic_error(whatArg) { }
};

class ExpressionTree
{
public:
	virtual ExpressionTree* Clone() const = 0;
};

#endif