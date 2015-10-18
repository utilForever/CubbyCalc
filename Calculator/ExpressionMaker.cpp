#include <vector>
#include <string>

#include "ExpressionMaker.h"

namespace
{
	const char* ops[]			= { "+", "-", "*", "/", "=", "^" };
	const int input_priority[]	= {  3,   3,   5,   5,   2,   8  };
	const int stack_priority[]	= {  4,   4,   6,   6,   1,   7  };
	const int n_ops= sizeof(ops) / sizeof(char*);

	const std::vector<std::string> operators(ops, ops + n_ops);
}