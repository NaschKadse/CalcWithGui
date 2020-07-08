#define _USE_MATH_DEFINES
#include "InputCheck.h"

InputCheck::InputCheck(string infix)
{

}
InputCheck::~InputCheck()
{

}

string InputCheck::checkInfix(string infix, double res) //zus�tzlicher Parameter double res um mit Ans rechnen zu k�nnen
{
	Calculator cal;
	stack<char> Stack1;
	bool rightInfix = true;
	int pointCounter = 0;
	int counterOperator = 0;
	int counterKlammeropen = 0;
	int SQRcounterKlammeropen = 0;
	int counterKlammerclose = 0;
	int SQRcounterKlammerclose = 0;
	string help;
	const bool debug = true;
	string root;
	double resultroot;
	QString msg;

	using namespace std;
	if (debug)
	{
		qDebug() << "-------------------------------------------------";
		qDebug() << "";
		msg = QString::fromStdString("Start Checking: " + infix);
		qDebug() << msg;
	}

	for (int i = 0; i < int(infix.length()); i++)
	{
		if (i < 0)
		{
			i = 0;
			qDebug() << "i kleiner 0!!";
		}
		if (infix[i] == '(') // Klammern behandeln
		{
			Stack1.push(infix[i]);
			if (debug)
			{
				msg = QString::fromStdString(to_string(i) + " Klammer ( auf Stack: " + infix);
				qDebug() << msg;
			}
		}
		if (infix[i] == ')')
		{
			if (debug)
			{
				msg = QString::fromStdString(to_string(i) + " Klammer ): " + infix);
				qDebug() << msg;
			}
			if (!Stack1.empty())
			{
				Stack1.pop();
			}
			else
			{
				throw(OwnException("too much )"));
			}
		}

		// Einf�gen um mit vorherigem Ergebnis als Ans weiterrechne zu k�nnen

		if ((infix[i] == 'A') && (infix[i+1] == 'n') && (infix[i+2] == 's')) //Result 
		{
			help = to_string(res);
			infix = infix.erase(i, 3);
			if ((i>=1)&&(isdigit(infix[i - 1])))
			{
				help = "*" +help;
				if (debug)
				{
					msg = QString::fromStdString(std::to_string(i) + " old Result1: " + infix);
					qDebug() << msg;
				}
			}
			if (isdigit(infix[i]))
			{
				help = help + "*";
				if (debug)
				{
					msg = QString::fromStdString(std::to_string(i) + " old Result2: " + infix);
					qDebug() << msg;
				}
			}
			infix = infix.insert(i, help);

			if (debug)
			{
				msg = QString::fromStdString(std::to_string(i) +  " old Result3: " + infix);
				qDebug() << msg;
			}
		}
		//End Ans

		if ((infix[i] == 'p') && (infix[i + 1] == 'i')) //Pi
		{
			if ((i <= (infix.size() - 2)) && (isdigit(infix[i + 2])))
			{
				infix = infix.insert((i + 2), "*");
				if (debug)
				{
					msg = QString::fromStdString(std::to_string(i) + " pi 1: " + infix);
					qDebug() << msg;
				}
			}

			double bla = M_PI;
			//help = to_string(M_PI);
			QString blaaa;
			blaaa = QString::number(bla, 'g', 10); //Pr�zision von 10
			help = blaaa.toStdString();
			infix = infix.erase(i, 2);
			infix = infix.insert(i, help);
			if (debug)
			{
				msg = QString::fromStdString(std::to_string(i) + " pi 2: " + infix);
				qDebug() << msg;
			}

			if ((i >= 1) && (isdigit(infix[i - 1])))
			{
				infix = infix.insert(i, "*");
				if (debug)
				{
					msg = QString::fromStdString(std::to_string(i) + " pi 3: " + infix);
					qDebug() << msg;
				}
			}

		}
		//Ende Pi

		if ((infix[i] == 's') && (infix[i + 1] == 'q') && (infix[i + 2] == 'r')) //Root
		{
			infix = infix.erase(i, 2);
			if (i >= 2)
			{
				i--;
			}
			else
			{
				i = 0;
			}
			
		}
		//Ende Wurzel

		if (isdigit(infix[i]))//Nummern sind ok
		{
			if (debug && (counterOperator > 0))
			{
				qDebug() << " set counterOperator = 0; ";
			}
			counterOperator = 0;
		}
		//Ende Ziffer
		else
		{
			if (cal.isOperator(infix[i])) //Behandlung von Operatoren
			{
				counterOperator++;
				pointCounter = 0;
				if ((i > 0) && ((infix[i - 1] == '(') || infix[i+1] == 'r'))
				{
					counterOperator = 0;
				}
				if (((i == 0) && (infix[i] != '-')) || (i == (infix.size()-1)))
				{
					infix = infix.erase(i, 1);
					i--; //String wird verschoben, deshalb muss der Index mit verchoben werden
					if (debug)
					{
						msg = QString::fromStdString(std::to_string(i) + " Operator 1: " + infix);
						qDebug() << msg;
					}
				}
				if (counterOperator > 1) //Wenn mehr als 1 Operator in Reihe ist wird dieser gel�scht
				{
					if ((infix[i] = infix[i + 1]) || (infix[i] == infix[i - 1]))
					{
						infix = infix.erase(i, 1);
						i--; //String wird verschoben, deshalb muss der Index mit verchoben werden
					}

					if ((isdigit(infix[i + 1]) && (infix[i] == '-') && (infix[i - 1] == '-')))
					{
						infix = infix.erase(i, 1);
						i--; //String wird verschoben, deshalb muss der Index mit verchoben werden
					}
					else 
					{
						if (debug)
						{
							msg = QString::fromStdString(to_string(i) + " Error: " + infix);
							qDebug() << msg;
						}
						throw (OwnException("double Operator"));
					}

					rightInfix = false;

					if (debug)
					{
						msg = QString::fromStdString(std::to_string(i) + " Operator 2: " + infix);
						qDebug() << msg;
					}

				}

				if ((counterOperator == 1) && (infix[i + 1] == '.')) //Ausnahme bei Operator und . : +.x --> +0.x
				{
					infix = infix.insert((i + 1), "0");
					rightInfix = false;
					if (debug)
					{
						msg = QString::fromStdString(std::to_string(i) + " Operator 3: " + infix);
						qDebug() << msg;
					}
				}
				if ((i != 0) && ((counterOperator == 1) && (infix[i + 1] == '-')) && ((infix[i - 1] == '(') || (infix[i + 1] == ')'))) //Ausnabme bei Klammern (+ --> (
				{
					infix = infix.erase(i, 1);
					i--; //String wird verschoben, deshalb muss der Index mit verchoben werden
					rightInfix = false;
					if (debug)
					{
						msg = QString::fromStdString(std::to_string(i) + " Operator 4: " + infix);
						qDebug() << msg;
					}
				}
			}
			else // Behandlung von unerlaubten Zeichen
			{
				if (infix[i] == '.') // . ist erlaubt, aber nicht x.xx.x.
				{
					pointCounter++;
					if (i == infix.length()) //l�schen des Punkts am Ende
					{
						pointCounter++;
						if (debug)
						{
							msg = QString::fromStdString(std::to_string(i) + " Point 1: " + infix);
							qDebug() << msg;
						}
					}
					if ((cal.isOperator(infix[i + 1])) || (infix[i + 1] == '(') || (infix[i + 1] == ')')) //. Vor Operator oder Klammer wird gel�scht
					{
						infix = infix.erase(i, 1);
						i--; //String wird verschoben, deshalb muss der Index mit verchoben werden
						rightInfix = false;
						if (debug)
						{
							msg = QString::fromStdString(std::to_string(i) + " Point 2: " + infix);
							qDebug() << msg;
						}
					}
					if (pointCounter > 1) //Behandlung von . Reihen
					{
						infix = infix.erase(i, 1);
						i--; //String wird verschoben, deshalb muss der Index mit verchoben werden
						rightInfix = false;
						if (debug)
						{
							msg = QString::fromStdString(std::to_string(i) + " Point 3: " + infix);
							qDebug() << msg;
						}
					}

				}
				else
				{
					//Klammer Behandlung
					if ((infix[i] == ')') && (i != infix.length()-1) && (isdigit(infix[i + 1]) ||(isalpha(infix[i+1]))) && (infix[i - 1] != '(')) // Behandlung )x --> )*x
					{
						infix = infix.insert((i + 1), "*");
						i++;
						rightInfix = false;
						if (debug)
						{
							msg = QString::fromStdString(std::to_string(i) + " Klammer 2: " + infix);
							qDebug() << msg;
						}
					}
					else
					{
						if ((infix[i] == '(') && (i != 0) && (isdigit(infix[i-1]) || (infix[i-1]== 'p') || (infix[i - 1] == ')')) && (infix[i + 1] != ')') && (i != (infix.size()-1))) //Behandlung x( --> x*(
						{
							infix = infix.insert(i, "*");
							i++;
							rightInfix = false;
							if (debug)
							{
								msg = QString::fromStdString(std::to_string(i) + " Klammer 3: " + infix);
								qDebug() << msg;
							}
						}
						else if (i > 0 && infix[i] == 'r' && isdigit(infix[i-1])) //Behandlung pisqr( --> pi*sqr(
						{
							infix = infix.insert(i, "*");
							i++;
							rightInfix = false;
							if (debug)
							{
								msg = QString::fromStdString(std::to_string(i) + " Klammer 4: " + infix);
								qDebug() << msg;
							}
						}
						
						
						else if ((infix[i] == ')') && (i != 0) && (infix[i - 1] == '(')) //L�schen einer leeren Klammer ()
						{
							infix = infix.erase((i - 1), 2);
							i--;
							rightInfix = false;
							if (debug)
							{
								msg = QString::fromStdString(std::to_string(i) + " Klammer 5: " + infix);
								qDebug() << msg;
							}
							if ((i != 0) && (infix[i] == '*') && (cal.isOperator(infix[i - 1])))
							{ //Behandeln von falsch eingef�gten Operatoren nach dem l�schen der leeren Klammer
								infix = infix.erase(i, 1);
								i--;
								rightInfix = false;
								if (debug)
								{
									msg = QString::fromStdString(std::to_string(i) + " Klammer 6: " + infix);
									qDebug() << msg;
								}
							}
							else if ((i != 0) && (infix[i - 1] == '*') && ((cal.isOperator(infix[i])) || (isdigit(infix[i]))))
							{
								infix = infix.erase((i - 1), 1);
								i--;
								rightInfix = false;
								if (debug)
								{
									msg = QString::fromStdString(std::to_string(i) + " Klammer 7: " + infix);
									qDebug() << msg;
								}
							}
						}
					}
				}
			}
		}
	}

	if (infix[0] == '.') // Am Anfang wird .xx korrigiert zu 0.xx
	{
		infix = "0" + infix;
		rightInfix = false;
	}

	while (!Stack1.empty()) // Klammer ) zu wenig
	{
		infix += ')';
		Stack1.pop();
		rightInfix = false;
		if (debug)
		{
			msg = QString::fromStdString("Klammer ) zu wenig: " + infix);
			qDebug() << msg;
		}
	}
	
	if (infix == "")
	{
		throw (OwnException("Error: Empty Input"));
	}
	if (debug) {
		rightInfix = false;

		//infix += "*"; //Fehler Test
	}

	if (!rightInfix) {
		msg = QString::fromStdString("= > Korrigierter Infix : " + infix);
		qDebug() << msg;
	}

	if (debug) {
		msg = QString::fromStdString("= > Infix : " + infix);
		qDebug() << msg;
		qDebug() << "";
		qDebug() << "-------------------------------------------------";
	}
	return infix;
}