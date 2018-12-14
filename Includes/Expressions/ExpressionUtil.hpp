#ifndef CUBBYCALC_EXPRESSION_UTIL_H
#define CUBBYCALC_EXPRESSION_UTIL_H

#include <string>
#include <stdexcept>

class InfixError : public std::logic_error
{
public:
	explicit InfixError(const std::string& whatArg) throw()
		: logic_error(whatArg) { }
};

std::string InfixToPostfix(const std::string& infix);

#endif