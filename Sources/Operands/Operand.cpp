#include <Operands/Operand.hpp>

#include <iomanip>
#include <sstream>

Operand::Operand()
{ }

Operand::Operand(const Operand& operandNode)
	: ExpressionTree(operandNode)
{ }

std::string Operand::GetPostfix() const
{
	return (ToString() + " ");
}

std::string Operand::GetInfix(bool) const
{
	return ToString();
}

void Operand::Print(std::ostream& os, int depth) const
{
	os << std::setw(depth) << ToString() << std::endl;
}