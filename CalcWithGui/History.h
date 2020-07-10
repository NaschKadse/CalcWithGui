#ifndef HISTORY_H
#define HISTORY_H

#include <string>
#include <vector>

#include "Calculator.h"


class History : public Calculator
{
public:
	History(std::string infix, double result);

	~History();

	void writeHistory(std::string m_infix, double  m_result);
	std::string outputInfix(int index);
	double outputResult(int index);

protected:

private:
	std::string m_infix = "";
	double m_result = 0.0;
	int m_index = 0;

};
#endif // !HISTORY_H