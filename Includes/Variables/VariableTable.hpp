#ifndef CUBBYCALC_VARIABLE_TABLE_HPP
#define CUBBYCALC_VARIABLE_TABLE_HPP

#include <map>
#include <string>
#include <stdexcept>

class VariableTableError : public std::logic_error
{
public:
	explicit VariableTableError(const std::string& whatArg) throw()
		: logic_error(whatArg) { }
};

class VariableTable
{
private:
	std::map<std::string, double> m_varTable;

public:
	VariableTable();
	~VariableTable();

	void Insert(const std::string&, const double&);
	void Remove(const std::string&);
	bool Find(const std::string&) const;
	double GetValue(const std::string&) const;
	void SetValue(const std::string&, const double&);
	void List(std::ostream&) const;
	void Clear();
	bool Empty() const;
};

#endif