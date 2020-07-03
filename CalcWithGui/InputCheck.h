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
		InputCheck(string infix);
		~InputCheck();
		string checkInfix(string infix, double res);

	protected:

	private:
};

#endif // !INPUTCHECK_H

