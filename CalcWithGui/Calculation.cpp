#include "Calculation.h"

Calculation::Calculation(std::string output) : m_output(output)
{

}
Calculation::~Calculation()
{

}

double error0_exeption(double t) {
	if (t == 0) {
		throw std::string("Math error: Division by Zero");
	}
	else {
		return t;
	}
}

double Calculation::calc(std::string m_output)
{
	std::stack <char> stack1;		// reversed stack
	std::stack <char> stack2;		// reversed (reversed stack) = normal stack
	std::stack <double> stack3;		// char to double stack
	std::string s_helper = "";		// variable to divide output string into pieces
	double d_helper = 0.0;		// variable to store substring as double
	double lValue = 0.0;		// left Calculation Value
	double rValue = 0.0;		// right Calculation Value
	double result = 0.0;		// intermediate result
	double endresult = 0.0;		// endresult
	QString msg;				// error message

	
	if (noOperator(m_output))
	{
		d_helper = stod(m_output);
		result = d_helper;
		d_helper = 0.0;
		stack3.push(result);
	}
	else
	{
		d_helper = 0.0;
		s_helper = "";
		for (unsigned int i = 0; i < m_output.length(); i++)
		{
			{
				if (isdigit(m_output[i]) || (m_output[i]) == '.' || (m_output[i]) == '-' && (isdigit(m_output[i + 1])))
				{
					stack1.push(m_output[i]);

				}
				else if ((i>0) && (m_output[i] == ' ') && (isdigit(m_output[i - 1])))
				{
					while (!stack1.empty())
					{
						stack2.push(stack1.top());
						stack1.pop();
					}
					while (!stack2.empty())
					{
						s_helper += stack2.top();
						stack2.pop();
					}

					d_helper = stod(s_helper);
					s_helper = "";
					stack3.push(d_helper);
					d_helper = 0.0;
				}
				else if (isOperator(m_output[i]) || (m_output[i] == 'r'))
				{
					if (m_output[i] == 'r')
					{
						if (stack3.empty())
						{
							throw(OwnException("Operant missing"));
						}
						lValue = stack3.top();
						stack3.pop();
						if (lValue < 0)
						{
							throw (OwnException("Negative Root"));
						}
						result = sqrt(lValue);
						stack3.push(result);
					}
					else if (m_output[i] == 'u')
					{
						lValue = stack3.top();
						stack3.pop();
						result = (-1)*(lValue);
						stack3.push(result);
					}
					else
					{
						if (stack3.empty())
						{
							throw(OwnException("Operant missing"));
						}
						rValue = stack3.top();
						stack3.pop();
						if (stack3.empty())
						{
							throw(OwnException("Operant missing"));
						}
						lValue = stack3.top();
						stack3.pop();

						if (m_output[i] == '+')
						{
							result = lValue + rValue;
							stack3.push(result);
						}
						else if (m_output[i] == '-')
						{
							result = lValue - rValue;
							stack3.push(result);
						}
						else if (m_output[i] == '*')
						{
							result = lValue * rValue;
							stack3.push(result);
						}
						else if (m_output[i] == '/')
						{
							if (rValue == 0) {
								throw (OwnException("Division by Zero"));
							}
							else {
								result = lValue / rValue;
								stack3.push(result);
							}
						}
						else if (m_output[i] == '^')
						{
							result = pow(lValue, rValue);
							stack3.push(result);
						}
					}
				}
			}
		}
	}
	endresult = stack3.top();
	
	return endresult;
}