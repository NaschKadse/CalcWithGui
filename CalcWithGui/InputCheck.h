#ifndef INPUTCHECK_H
#define INPUTCHECK_H

#include "Calculation.h"
#include "RPN.h"
#include <iostream>
#include <string>
#include "OwnException.h"
#include <qstring.h>
#include <QDebug>
#include <stack>
#include <cmath>
#include <math.h>

using namespace std;

class InputCheck
{
	public:
		InputCheck(string root);
		~InputCheck();
		string checkInfix(string infix);

	protected:

	private:
		string checkRoot(string m_root);
		string m_root = "";
};

#endif // !INPUTCHECK_H

