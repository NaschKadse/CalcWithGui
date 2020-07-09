#include "Calculation.h"


Calculation::Calculation(std::string output) : m_output(output)
{

}
Calculation::~Calculation()
{

}


// rounding function
double Calculation::Round(double Number, int decimals)
{
	double v[] = { 1, 10, 1e2, 1e3, 1e4, 1e5, 1e6, 1e7, 1e8 };
	return floor(Number * v[decimals] + 0.5) / v[decimals];
}


// calculation function
double Calculation::calc(std::string m_output)
{
	std::stack <char> stack1;		// reversed stack
	std::stack <char> stack2;		// reversed (reversed stack) = normal stack
	std::stack <double> stack3;		// char to double stack
	std::string s_helper = "";		// variable to divide output string into pieces
	double d_helper = 0.0;			// variable to store substring as double
	double lValue = 0.0;			// left Calculation Value
	double rValue = 0.0;			// right Calculation Value
	double result = 0.0;			// intermediate result
	double endresult = 0.0;			// endresult
	QString msg;					// error message
	

	// no operator in string
	if (noOperator(m_output))
	{
		d_helper = stod(m_output);
		result = d_helper;
		d_helper = 0.0;
		stack3.push(result);
	}
	else
	{
		for (unsigned int i = 0; i < m_output.length(); i++)
		{
			{
				// numeric || . || - && successor numeric
				if (isdigit(m_output[i]) || (m_output[i]) == '.' /*|| (m_output[i]) == '-' && (isdigit(m_output[i + 1]))*/)
				{
					stack1.push(m_output[i]);

				}
				// if a space is read after a number, the number is moved to stack1 and then to stack2 to rotate it
				// i > 0 && space && predecessor numeric
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

					d_helper = stod(s_helper);	// string -> double
					s_helper = "";				// clean
					stack3.push(d_helper);		// double -> stack3
					d_helper = 0.0;				// clean
				}
				// check operator and execute the corresponding function
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
							result  = lValue * rValue;
							result = Round(result, 5);  // round to maximum display length -1
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
	endresult = Round(endresult, 6); // round to maximum display length
	
	return endresult;
}