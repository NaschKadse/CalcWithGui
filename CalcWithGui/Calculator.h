#ifndef CALCULATOR_H
#define CALCULATOR_H

#include "Calculator.h"
#include <iostream>
#include <string>
#include <iomanip>
#include "OwnException.h"


using namespace std;

class Calculator
{
public:
	Calculator();
	Calculator(string input);
	~Calculator();
	virtual bool isOperator(char c);
	virtual bool noOperator(string output);

protected:

private:

};

#endif // !CALCULATOR_H