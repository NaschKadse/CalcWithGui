#ifndef INPUTCHECK_H
#define INPUTCHECK_H

#include <qstring.h>
#include <QDebug>
#include <stack>
#include <cmath>
#include <math.h>
#include <string>

#include "Calculation.h"
#include "RPN.h"
#include "OwnException.h"

class InputCheck : public Calculator
{
	public:
		InputCheck(std::string infix);

		~InputCheck();

		std::string checkInfix(std::string infix, double res);

	protected:

	private:
};

#endif // !INPUTCHECK_H

