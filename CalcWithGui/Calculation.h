#ifndef CALCULATION_H
#define CALCULATION_H

#include <iostream>
#include <string>
#include "Calculator.h"
#include <iomanip>
#include <string.h>
#include <stack>
#include <iomanip>
#include <QDebug>

#include "OwnException.h"

using namespace std;

class Calculation : public Calculator
{
public:
	Calculation(string output);
	~Calculation();
	double calc(string output);

protected:

private:
	string m_output;
	string m_minus;
};

#endif // !CALCULATION_H