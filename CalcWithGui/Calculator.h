#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <iostream>
#include <string>
#include "Calculator.h"
#include <iomanip>

using namespace std;

class Calculator
{
public:
	Calculator();
	Calculator(string input);
	~Calculator();
	virtual bool isOperator(char c);
	virtual bool noOperator(string output);
	string checkInfix(string infix, double res);
	char checkPreMinus(string infix);

protected:

private:

};

#endif // !CALCULATOR_H