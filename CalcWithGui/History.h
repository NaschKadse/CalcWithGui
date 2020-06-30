#ifndef HISTORY_H
#define HISTORY_H

#include "Calculator.h"
#include <string>


class History : public Calculator
{
public:
	History(string infix, double result);
	History(int index);
	~History();
	void writeHistory(string m_infix, double  m_result);
	string outputInfix(int index);
	double outputResult(int index);

protected:

private:
	string m_infix = "";
	double m_result = 0.0;
	int m_index = 0;

};
#endif // !HISTORY_H