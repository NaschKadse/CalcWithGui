#ifndef RPN_H
#define RPN_H

#include "Calculator.h"
#include <string>
#include <iostream>
#include <stack>

class RPN :
	public Calculator
{
public:

	RPN(string infix);

	~RPN();

	string m_infix;

	int precedence(char c);
	string infixToPostfix(stack<char>stack, string infix);

protected:

private:

};

#endif // !RPN_H