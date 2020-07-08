#ifndef RPN_H
#define RPN_H

#include <string>
#include <iostream>
#include <stack>

#include "Calculator.h"


class RPN :
	public Calculator
{
public:

	RPN(std::string infix);

	~RPN();

	std::string m_infix;

	int precedence(char c);
	std::string infixToPostfix(std::stack<char>stack, std::string infix);

protected:

private:

};

#endif // !RPN_H