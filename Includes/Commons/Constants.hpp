#ifndef CUBBYCALC_CONSTANTS_HPP
#define CUBBYCALC_CONSTANTS_HPP

#include <map>
#include <vector>
#include <string>

namespace
{
	const char* ops[] = { "+", "-", "*", "/", "=", "^", "u-", "sin", "cos", "tan", "(" };
	const int init_input_priority[] = { 4, 4, 5, 5, 1, 6, 7, 7, 7, 7, 8 };
	const int init_stack_priority[] = { 4, 4, 5, 5, 1, 6, 7, 7, 7, 7, 0 };
	const int n_ops = sizeof(ops) / sizeof(char*);

	const std::vector<std::string> operators(ops, ops + n_ops);

	const std::string digits("0123456789");
	const std::string integer_chars(digits);
	const std::string real_chars(digits + '.');
	const std::string identifier_chars("abcdefghijklmnopqrstuvwxyz");
	const std::string operand_chars(identifier_chars + digits + '.');

	typedef std::map<std::string, int> priority_table;

	priority_table init_priority_table(const char* op_list[], const int* priority, const int n_op_list)
	{
		priority_table temp;

		for (int i = 0; i < n_op_list; ++i)
		{
			temp.insert(std::make_pair(std::string(op_list[i]), priority[i]));
		}

		return temp;
	}

	const priority_table input_priority = init_priority_table(ops, init_input_priority, n_ops);
	const priority_table stack_priority = init_priority_table(ops, init_stack_priority, n_ops);
}

#endif