#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <string>

#include "OwnException.h"
#include "Calculator.h"


class Calculator
{
public:
	Calculator();
	Calculator(std::string input);
	~Calculator();
	virtual bool isOperator(char c);
	virtual bool noOperator(std::string output);

protected:

private:

};

#endif // !CALCULATOR_H