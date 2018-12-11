#include <Variables/VariableTable.hpp>

#include <string>
#include <map>
#include <iostream>

typedef std::map<std::string, double> variable_table;

VariableTable::VariableTable()
{ }

VariableTable::~VariableTable()
{ }

void VariableTable::Insert(const std::string& token, const double& value)
{
	if (Find(token))
	{
		throw VariableTableError("Error: Token already exists");
	}

	m_varTable.insert(std::make_pair(token, value));
}

void VariableTable::Remove(const std::string& token)
{
	if (!Find(token))
	{
		throw VariableTableError("Error: Token not exists");
	}

	m_varTable.erase(token);
}

bool VariableTable::Find(const std::string& token) const
{
	return (m_varTable.find(token) != m_varTable.end());
}

double VariableTable::GetValue(const std::string& token) const
{
	variable_table::const_iterator iter = m_varTable.find(token);
	
	if (iter == m_varTable.end())
	{
		throw VariableTableError("Error: Can't find token");
	}

	return iter->second;
}

void VariableTable::SetValue(const std::string& token, const double& value)
{
	variable_table::iterator iter = m_varTable.find(token);

	if (iter == m_varTable.end())
	{
		throw VariableTableError("Error: Can't find token");
	}

	iter->second = value;
}

void VariableTable::List(std::ostream& os) const
{
	for (auto token : m_varTable)
	{
		os << token.first << ": " << token.second << std::endl;
	}
}

void VariableTable::Clear()
{
	m_varTable.clear();
}

bool VariableTable::Empty() const
{
	return m_varTable.empty();
}