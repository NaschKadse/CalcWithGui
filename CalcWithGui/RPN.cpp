#include "RPN.h"

RPN::RPN(std::string m_infix) : m_infix(m_infix)
{

}
RPN::~RPN()
{

}

// Operator precedence function
int RPN::precedence(char c)
{
	if (c == 'u')
	{
		return 4;
	}
	else if (c == '^' || c == 'r')
	{
		return 3;
	}
	else if (c == '*' || c == '/')
	{
		return 2;
	}
	else if (c == '+' || c == '-')
	{
		return 1;
	}
	else
	{
		return -1;
	}
}

std::string RPN::infixToPostfix(std::stack<char>stack, std::string m_infix)
{

	std::string postfix;
	std::string postpostfix;
	std::string test;
	std::string spacer = " ";

	for (int i = 0; i < m_infix.length(); i++)
	{
		if ((i==0 && m_infix[i] == '-') || (m_infix[i] == '-' && m_infix[i - 1] == '('))
		{
			m_infix[i] = 'u';
		}

		if (m_infix[i] >= '0' && m_infix[i] <= '9' || m_infix[i] == '.')
		{
			postfix += m_infix[i];
		}

		//Pre Numeric Spacer
		if ((isdigit(m_infix[i]) && isOperator(m_infix[i + 1])) || (m_infix[i] == ')' && (isOperator(m_infix[i + 1]) || m_infix[i + 1] == 'r')))
		{
			postfix += spacer;
		}

		//Opening Bracket pushing to stack
		if (m_infix[i] == '(')
		{
			stack.push(m_infix[i]);
		}
		else if (m_infix[i] == ')')
		{
			// if a closed bracket is read and there is no opening bracket
			// at the top of the stack and the stack is not empty, write the 
			// top of the stack into the string and pop the stack
			while (stack.top() != '(' && (!stack.empty()))
			{
				postfix = postfix + spacer + stack.top();
				stack.pop();
			}
			// if a closed bracket is read and an opening bracket is on top of the stack, remove it
			if (stack.top() == '(')
			{
				stack.pop();
			}
		}
		// Operator Check
		else if (((isOperator(m_infix[i]) && i > 0 && m_infix[i - 1] != '(') || m_infix[i] == 'r'|| m_infix[i] == 'u'))
		{
			// Push Operator to Stack if stack is empty
			if (stack.empty())
			{
				stack.push(m_infix[i]);
				test += stack.top();
			}
			// Check Precedence
			else
			{
				// If operator has priority put it on the stack
				if (precedence(m_infix[i]) > precedence(stack.top()))
				{
					stack.push(m_infix[i]);
				}
				// if the operator priority is equal and the operator is '^'
				else if ((precedence(m_infix[i]) == precedence(stack.top())) && (m_infix[i] == '^'))
				{
					stack.push(m_infix[i]);
				}
				// if the operator has the same or lower priority
				else
				{
					while ((!stack.empty() && (precedence(m_infix[i]) <= precedence(stack.top()))))
					{
						postfix = postfix + stack.top() + spacer;
						stack.pop();
					}
					stack.push(m_infix[i]);
				}
			}
		}
	}
	// write in the string until the stack is empty
	while (!stack.empty())
	{
		postfix = postfix + spacer + stack.top();
		stack.pop();
	}
	return postfix;
}