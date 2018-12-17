#ifndef CUBBYCALC_CONSTANTS_HPP
#define CUBBYCALC_CONSTANTS_HPP

#include <map>
#include <string>
#include <vector>

namespace CubbyCalc
{
constexpr const char* OPERATORS[] = { "+",  "-",   "*",   "/",   "=", "^",
                                      "u-", "sin", "cos", "tan", "(" };
constexpr size_t OPERATORS_SIZE = sizeof(OPERATORS) / sizeof(const char*);

constexpr int INIT_INPUT_PRIORITY[] = { 4, 4, 5, 5, 1, 6, 7, 7, 7, 7, 8 };
constexpr int INIT_STACK_PRIORITY[] = { 4, 4, 5, 5, 1, 6, 7, 7, 7, 7, 0 };

const std::string DIGITS("0123456789");
const std::string INTEGER_CHARS(DIGITS);
const std::string REAL_CHARS(DIGITS + '.');

const std::string ID_CHARS("abcdefghijklmnopqrstuvwxyz");
const std::string OPERAND_CHARS(ID_CHARS + DIGITS + '.');

using PriorityTable = std::map<std::string, int>;

inline PriorityTable InitPriorityTable(const char* const opList[],
                                       const size_t opSize, const int* priority)
{
    PriorityTable temp;

    for (size_t i = 0; i < opSize; ++i)
    {
        temp.insert(std::make_pair(std::string(opList[i]), priority[i]));
    }

    return temp;
}

const PriorityTable INPUT_PRIORITY =
    InitPriorityTable(OPERATORS, OPERATORS_SIZE, INIT_INPUT_PRIORITY);
const PriorityTable STACK_PRIORITY =
    InitPriorityTable(OPERATORS, OPERATORS_SIZE, INIT_STACK_PRIORITY);
}  // namespace CubbyCalc

#endif