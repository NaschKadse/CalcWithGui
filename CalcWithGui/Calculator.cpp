#include "Calculator.h"


Calculator::Calculator()
{

}
Calculator::Calculator(std::string input)
{

}
Calculator::~Calculator()
{

}


bool Calculator::isOperator(char c)
{
	if (c == '+' || c == '-' || c == '*' || c == '/' || c == '^' || c == 'u' || c == 'r')
	{
		return true;
	}
	else
	{
		return false;
	}
}


bool Calculator::noOperator(std::string output)
{
	bool check = true;

	for (unsigned int i = 0; i < output.length(); i++)
	{
		if (i == 0 && output[i] == '-')
		{
			check = true;
		}
		if (Calculator::isOperator(output[i]) && i < 0 || output[i] == ' ')
		{
			check = false;
		}
	}
	return check;
}

