#define _USE_MATH_DEFINES
#include "InputCheck.h"

InputCheck::InputCheck(std::string infix)
{

}
InputCheck::~InputCheck()
{

}

std::string InputCheck::checkInfix(std::string infix, double res)
{
	Calculator cal; //Hilfsobjekt um inOperator verwenden zu können
	std::stack<char> StackKlammeropen; // Zwischenspeicher für die offenen Klammern
	bool rightInfix = true; // Status ob der Infix korrekt ist/war oder nicht
	int pointCounter = 0; // Zähler für die vorhandenen Punkte zwischen zwei Operatoren
	int counterOperator = 0; //Anzahl Operatoren zwischen 2 Zahlen
	std::string help; //String Zwischnenspeicher
	std::string root; //Alles unter der Wurzel
	double resultroot; //Ergebnis  der Wurzelrechnung
	QString msg; // debugg message
	const bool debug = false; //Anzeige der Debugg Meldungen

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
			StackKlammeropen.push(infix[i]);
			if (debug)
			{
				msg = QString::fromStdString(std::to_string(i) + " Klammer ( auf Stack: " + infix);
				qDebug() << msg;
			}
		}
		if (infix[i] == ')')
		{
			counterOperator = 0;
			pointCounter = 0;

			if (debug)
			{
				msg = QString::fromStdString(std::to_string(i) + " Klammer ): " + infix);
				qDebug() << msg;
			}
			if (!StackKlammeropen.empty())
			{
				StackKlammeropen.pop();
			}
			else
			{
				throw(OwnException("too much )"));
			}
		}

		// Einfügen um mit vorherigem Ergebnis als Ans weiterrechne zu können

		if ((infix[i] == 'A') && (infix[i + 1] == 'n') && (infix[i + 2] == 's')) //Result 
		{
			help = std::to_string(res);
			infix = infix.erase(i, 3);
			if ((i >= 1) && (isdigit(infix[i - 1])))
			{
				help = "*" + help;
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
				msg = QString::fromStdString(std::to_string(i) + " old Result3: " + infix);
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

			double pi = M_PI;
			//help = to_string(M_PI);
			QString blaaa;
			blaaa = QString::number(pi, 'f', 12); //Präzision von 10
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
			msg = QString::fromStdString(std::to_string(i) + " " + infix[i] + "   " + std::to_string(counterOperator) +"   " + infix);
			qDebug() << msg;

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
				if ((i > 0) && ((infix[i - 1] == '(') || infix[i + 1] == 'r')) //
				{
					counterOperator = 0;
				}
				if (((i == 0) && (infix[i] != '-')) || (i == (infix.size() - 1))) //einzelne Operatoren am Anfang und Ende werden gelöscht
				{
					infix = infix.erase(i, 1);
					i--; //String wird verschoben, deshalb muss der Index mit verchoben werden
					if (i < 0)
					{
						i = 0;
					}
					if (debug)
					{
						msg = QString::fromStdString(std::to_string(i) + " " + infix[i] + " Operator 1: " + infix);
						qDebug() << msg;
					}
				}

				if (counterOperator > 1) //Wenn mehr als 1 Operator in Reihe ist wird dieser gelöscht
				{
					if ((i>0)&&(infix[i-1] == infix[i])) //genau gleicher Operator
					{
						if (infix[i] == '-')
						{
							if (i > 0) { //Minus Minus ist Plus
								infix = infix.erase((i - 1), 2);
								infix = infix.insert((i - 1), "+");
								if (debug)
								{
									msg = QString::fromStdString(std::to_string(i) + " " +infix[i] + " Operator 2.1.1: " + infix);
									qDebug() << msg;
								}
								i = i - 2;
							}
						}
						else
						{
							infix = infix.erase((i-1), 1);
							if (debug)
							{
								msg = QString::fromStdString(std::to_string(i)+" "+infix[i] + " Operator 2.1.2: " + infix);
								qDebug() << msg;
							}
							i=i-2;
						}
						counterOperator = 0;
					}

					else if ((i>0) && cal.isOperator(infix[i]) && cal.isOperator(infix[i-1]))
					{
						if (infix[i] == '-' || infix[i - 1] == '-')
						{
							infix = infix.erase((i - 1), 2);
							infix = infix.insert((i - 1), "-");
							if (debug)
							{
								msg = QString::fromStdString(std::to_string(i) + " " + infix[i] + " Operator 2.2: " + infix);
								qDebug() << msg;
							}
							i = i - 2;
							counterOperator = 0;
						}

					}
					else if ((i > 0) && ((isdigit(infix[i + 1]) && (infix[i] == '-') &&  (infix[i - 1] == '-'))))
					{
						infix = infix.erase(i, 1);
						i--; //String wird verschoben, deshalb muss der Index mit verchoben werden
						if (debug)
						{
							msg = QString::fromStdString(std::to_string(i) + " " + infix[i] + " Operator 2.3: " + infix);
							qDebug() << msg;
						}
					}
					else
					{
						if (debug)
						{
							msg = QString::fromStdString(std::to_string(i) + " Error: " + infix + " Anzahl Operatoren: "+std::to_string(counterOperator));
							qDebug() << msg;
						}
						throw (OwnException("double Operator"));
					}

					rightInfix = false;

				}

				//Ausnahme bei Operator und . : +.x --> +0.x
				if ((counterOperator == 1) && (infix[i + 1] == '.')) 
				{
					infix = infix.insert((i + 1), "0");
					rightInfix = false;
					if (debug)
					{
						msg = QString::fromStdString(std::to_string(i) + " Operator 3: " + infix);
						qDebug() << msg;
					}
				}

				//Ausnabme bei Klammern (+ --> (
				if ((i != 0) && ((counterOperator == 1) && (infix[i + 1] == '-')) && ((infix[i - 1] == '(') || (infix[i + 1] == ')'))) 
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
					if (i == infix.length()) //löschen des Punkts am Ende
					{
						pointCounter++;
						if (debug)
						{
							msg = QString::fromStdString(std::to_string(i) + " Point 1: " + infix);
							qDebug() << msg;
						}
					}

					//. Vor Operator oder Klammer wird gelöscht
					if ((cal.isOperator(infix[i + 1])) || (infix[i + 1] == '(') || (infix[i + 1] == ')')) 
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

					// Behandlung )x --> )*x
					if ((infix[i] == ')') && (i != infix.length() - 1) && (isdigit(infix[i + 1]) || (isalpha(infix[i + 1]))) && (infix[i - 1] != '(')) 
					{
						infix = infix.insert((i + 1), "*");
						i++;
						rightInfix = false;
						if (debug)
						{
							msg = QString::fromStdString(std::to_string(i) + " Klammer 1: " + infix);
							qDebug() << msg;
						}
					}
					else
					{
						//Behandlung x( --> x*(
						if ((infix[i] == '(') && (i != 0) && (isdigit(infix[i - 1]) || (infix[i - 1] == 'p') || (infix[i - 1] == ')')) && (infix[i + 1] != ')') && (i != (infix.size() - 1))) 
						{
							infix = infix.insert(i, "*");
							i++;
							rightInfix = false;
							if (debug)
							{
								msg = QString::fromStdString(std::to_string(i) + " Klammer 2: " + infix);
								qDebug() << msg;
							}
						}
						else if (i > 0 && infix[i] == 'r' && isdigit(infix[i - 1])) //Behandlung pisqr( --> pi*sqr(
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

						//Löschen einer leeren Klammer ()
						else if ((infix[i] == ')') && (i != 0) && (infix[i - 1] == '('))
						{
							infix = infix.erase((i - 1), 2);
							if (debug)
							{
								msg = QString::fromStdString(std::to_string(i) + " Klammer 4.1: " + infix);
								qDebug() << msg;
							}
							i=i-2;
							msg = QString::fromStdString(std::to_string(i) + " " + infix[i]);
							qDebug() << msg; //Test
							rightInfix = false;
							
							if (infix[i] == 'r') {
								infix = infix.erase(i, 1);
								if (debug)
								{
									msg = QString::fromStdString(std::to_string(i) + " Klammer 4.2: " + infix);
									qDebug() << msg;
								}
								i--;
							}

							//tod? Klammer 4.2 & Klammer 4.3
							if ((i > 0) && (infix[i] == '*') && (cal.isOperator(infix[i - 1])))
							{ //Behandeln von falsch eingefügten Operatoren nach dem löschen der leeren Klammer
								infix = infix.erase(i, 1);
								i--;
								rightInfix = false;
								if (debug)
								{
									msg = QString::fromStdString(std::to_string(i) + " Klammer 4.3: " + infix);
									qDebug() << msg;
								}
							}
							else if ((i > 0) && (infix[i - 1] == '*') && ((cal.isOperator(infix[i])) || (isdigit(infix[i]))))
							{
								infix = infix.erase((i - 1), 1);
								i--;
								rightInfix = false;
								if (debug)
								{
									msg = QString::fromStdString(std::to_string(i) + " Klammer 4.4: " + infix);
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

	while (!StackKlammeropen.empty()) // Klammer ) zu wenig
	{
		infix += ')';
		StackKlammeropen.pop();
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