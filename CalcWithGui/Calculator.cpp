#include "Calculator.h"


Calculator::Calculator()
{

}
Calculator::Calculator(string input)
{

}
Calculator::~Calculator()
{

}
bool Calculator::isOperator(char c)
{
	if (c == '+' || c == '-' || c == '*' || c == '/' || c == '^')
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Calculator::noOperator(string output)
{
	bool check = true;
	//std::cout << "Use noOperator" << endl; //Test
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