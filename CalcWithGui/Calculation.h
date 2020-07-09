#ifndef CALCULATION_H
#define CALCULATION_H

#include <string>
#include <stack>
#include <QDebug>

#include "Calculator.h"
#include "OwnException.h"


class Calculation : public Calculator
{
public:
	Calculation(std::string output);
	~Calculation();
	double calc(std::string output);
	double Round(double Number, int decimals);

protected:

private:
	double Round(double Number, unsigned int decimals);
	std::string m_output;
	std::string m_minus;
};

#endif // !CALCULATION_H