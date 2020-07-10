#ifndef CALCULATION_H
#define CALCULATION_H

#include <string>
#include <stack>
#include <QDebug>
#include <cmath>
#include <limits>
#include <iomanip>

#include "Calculator.h"
#include "OwnException.h"


class Calculation : public Calculator
{
public:
	Calculation(std::string output);
	~Calculation();

	double calc(std::string output);

protected:

private:
	double Round(double Number, int decimals);
	std::string m_output;
	std::string m_minus;
};

#endif // !CALCULATION_H