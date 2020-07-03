#define _USE_MATH_DEFINES
#include "InputCheck.h"

InputCheck::InputCheck(string root) : m_root(root)
{

}
InputCheck::~InputCheck()
{

}

string InputCheck::checkRoot(string m_root)
{
	stack<char> Stack1;
	stack<char> Stack2;
	string help;
	Calculation calcu(help);
	bool isRoot = false;
	bool debug = true;
	double result;
	string h;
	QString msg;

	

	h = m_root;
	if (debug)
	{
		msg = QString::fromStdString("Wurzelbehandlung: " + h);
		qDebug() << msg;
	}

	for (int i = 0; i < m_root.length(); i++)
	{
		//root.find("sqr") > 0
		if ((m_root[i] == 's') && (m_root[i + 1] == 'q') && (m_root[i + 2] == 'r')) {
			isRoot = true;
			m_root = m_root.erase(i, 3);
			if (debug)
			{
				msg = QString::fromStdString(to_string(i) + " isRoot = true " + m_root);
				qDebug() << msg;
			}
		}
		if ((m_root[i] == '(') && isRoot)
		{
			Stack1.push(m_root[i]);
			if (debug)
			{
				msg = QString::fromStdString(to_string(i) + " ( " + m_root);
				qDebug() << msg;
			}
		}
		if ((!Stack1.empty()) && isRoot)
		{
			help = help + m_root[i];
		}
		if ((m_root[i] == ')') && isRoot)
		{
			Stack1.pop();
			if (debug)
			{
				msg = QString::fromStdString(to_string(i) + " ) " + m_root);
				qDebug() << msg;
			}
			if (Stack1.empty())
			{
				while (!(Stack2.empty()))
				{
					Stack2.pop();
				}
				RPN rootItoP(help);
				help = rootItoP.infixToPostfix(Stack2,  help);
				result = calcu.calc(help);
				isRoot = false;
				if (result < 0)
				{
					throw (OwnException("Negative Root\n \n"));
				}
				else
				{
					m_root = m_root.insert(i, "^(1/2)");
					if (debug)
					{
						msg = QString::fromStdString(to_string(i) + " Korrekt: " + m_root);
						qDebug() << msg;
					}
				}
			}
		}
	}
	return m_root;
}

string InputCheck::checkInfix(string infix) //zusätzlicher Parameter double res um mit Ans rechnen zu können
{
	Calculator cal;
	bool rightInfix = true;
	int pointCounter = 0;
	int counterOperator = 0;
	int counterKlammeropen = 0;
	int SQRcounterKlammeropen = 0;
	int counterKlammerclose = 0;
	int SQRcounterKlammerclose = 0;
	string help;
	const bool debugg = true;
	string root;
	double resultroot;
	QString msg;

	using namespace std;
	if (debugg)
	{
		qDebug() << "-------------------------------------------------";
		qDebug() << "";
		msg = QString::fromStdString("Start Checking: " + infix);
		qDebug() << msg;
	}
	//infix = std::tolower();

	for (int i = 0; i < int(infix.length()); i++)
	{
		if (i < 0)
		{
			i = 0;
			qDebug() << "i kleiner 0!!";
		}
		if (infix[i] == '(') // Klammern behandeln
		{
			counterKlammeropen++;
		}
		if (infix[i] == ')')
		{
			counterKlammerclose++;
		}

		// Einfügen um mit vorherigem Ergebnis als Ans weiterrechne zu können

		//if ((infix[i] == 'a') && (infix[i+1] == 'n') && (infix[i+2] == 's')) //Result 
		//{
		//	help = to_string(res);
		//	infix = infix.replace(i, 1, help);
		//	if (debugg)
		//	{
		//		std::cout << i << " old Result: " << infix << endl; //Test
		//	}
		//}
		if ((infix[i] == 'p') && (infix[i + 1] == 'i')) //Pi
		{
			if ((i <= (infix.size() - 2)) && (isdigit(infix[i + 2])))
			{
				infix = infix.insert((i + 2), "*");
				if (debugg)
				{
					msg = QString::fromStdString(std::to_string(i) + " pi 1: " + infix);
					qDebug() << msg;
				}
			}

			help = to_string(M_PI);
			infix = infix.erase(i, 2);
			infix = infix.insert(i, help);
			if (debugg)
			{
				msg = QString::fromStdString(std::to_string(i) + " pi 2: " + infix);
				qDebug() << msg;
			}

			if ((i >= 1) && (isdigit(infix[i - 1])))
			{
				infix = infix.insert(i, "*");
				if (debugg)
				{
					msg = QString::fromStdString(std::to_string(i) + " pi 3: " + infix);
					qDebug() << msg;
				}
			}

		}
		//Ende Pi

		if (isdigit(infix[i]))//Nummern sind ok
		{
			if (debugg && (counterOperator > 0))
			{
				qDebug() << " set counterOperator = 0; ";
			}
			counterOperator = 0;
		}
		else
		{
			if (cal.isOperator(infix[i])) //Behandlung von Operatoren
			{
				counterOperator++;
				pointCounter = 0;
				if ((i > 0) && (infix[i - 1] == '('))
				{
					counterOperator = 0;
				}
				if (((i == 0) && (infix[i] != '-')) || (i == (infix.size())))
				{
					counterOperator++;
					if (debugg)
					{
						msg = QString::fromStdString(std::to_string(i) + " Operator 1: " + infix);
						qDebug() << msg;
					}
				}
				if (counterOperator > 1) //Wenn mehr als 1 Operator in Reihe ist wird dieser gelöscht
				{
					if ((isdigit(infix[i + 1]) && (infix[i] == '-') && (infix[i - 1] == '-')))
					{
						infix = infix.erase(i, 1);
						i--; //String wird verschoben, deshalb muss der Index mit verchoben werden
					}

					rightInfix = false;

					if (debugg)
					{
						msg = QString::fromStdString(std::to_string(i) + " Operator 2: " + infix);
						qDebug() << msg;
					}

				}

				if ((counterOperator == 1) && (infix[i + 1] == '.')) //Ausnahme bei Operator und . : +.x --> +0.x
				{
					infix = infix.insert((i + 1), "0");
					rightInfix = false;
					if (debugg)
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
					if (debugg)
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
						if (debugg)
						{
							msg = QString::fromStdString(std::to_string(i) + " Point 1: " + infix);
							qDebug() << msg;
						}
					}
					if ((cal.isOperator(infix[i + 1])) || (infix[i + 1] == '(') || (infix[i + 1] == ')')) //. Vor Operator oder Klammer wird gelöscht
					{
						infix = infix.erase(i, 1);
						i--; //String wird verschoben, deshalb muss der Index mit verchoben werden
						rightInfix = false;
						if (debugg)
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
						if (debugg)
						{
							msg = QString::fromStdString(std::to_string(i) + " Point 3: " + infix);
							qDebug() << msg;
						}
					}

				}
				else
				{
					//Klammer Behandlung
					if ((infix[i] == ')') && (counterKlammeropen < counterKlammerclose)) //Fehlende Klammer auf
					{
						infix = infix.erase(i, 1);
						i--;
						counterKlammerclose--;
						rightInfix = false;
						if (debugg)
						{
							help = i + " Klammer 1: " + infix + "   Counter(): " + std::to_string(counterKlammeropen) + " " + std::to_string(counterKlammerclose);
							msg = QString::fromStdString(help);
							qDebug() << msg;
						}
					}
					else
					{
						if ((infix[i] == ')') && (i != infix.length()) && (isdigit(infix[i + 1]) && (infix[i - 1] != '('))) // Behandlung )x --> )*x
						{
							infix = infix.insert((i + 1), "*");
							i++;
							rightInfix = false;
							if (debugg)
							{
								msg = QString::fromStdString(std::to_string(i) + " Klammer 2: " + infix);
								qDebug() << msg;
							}
						}
						else
						{
							if ((infix[i] == '(') && (i != 0) && (isdigit(infix[i - 1]) && (infix[i + 1] != ')'))) //Behandlung x( --> x*(
							{
								infix = infix.insert(i, "*");
								i++;
								rightInfix = false;
								if (debugg)
								{
									msg = QString::fromStdString(std::to_string(i) + " Klammer 3: " + infix);
									qDebug() << msg;
								}
							}
							else
							{
								if ((infix[i] == ')') && (i != 0) && (infix[i - 1] == '(')) //Löschen einer leeren Klammer
								{
									infix = infix.erase((i - 1), 2);
									i--;
									rightInfix = false;
									if (debugg)
									{
										msg = QString::fromStdString(std::to_string(i) + " Klammer 4: " + infix);
										qDebug() << msg;
									}
									if ((i != 0) && (infix[i] == '*') && (cal.isOperator(infix[i - 1])))
									{//Behandeln von falsch eingefügten Operatoren nach dem löschen der leeren Klammer
										infix = infix.erase(i, 1);
										i--;
										rightInfix = false;
										if (debugg)
										{
											msg = QString::fromStdString(std::to_string(i) + " Klammer 5: " + infix);
											qDebug() << msg;
										}
									}
									else
									{
										if ((i != 0) && (infix[i - 1] == '*') && ((cal.isOperator(infix[i])) || (isdigit(infix[i]))))
										{
											infix = infix.erase((i - 1), 1);
											i--;
											rightInfix = false;
											if (debugg)
											{
												msg = QString::fromStdString(std::to_string(i) + " Klammer 6: " + infix);
												qDebug() << msg;
											}
										}
									}
								}

								else
								{
									/* Nur Benötigt bei Tastertureingabe
									if ((infix[ii] != ('(' || 's' || 'q' || 'r' )) && (infix[i] != ')'))
									{
										//Sonderzeichen und Buchstaben Behandlung
										infix = infix.erase(i, 1);
										i--;
										rightInfix = false;
										if (debugg)
										{
											msg = QString::fromStdString(std::to_string(i) + " Sonstiges: " + infix);
											qDebug() << msg;
										}
									}
									*/
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

	while (counterKlammeropen > counterKlammerclose) // Klammer ) zu wenig
	{
		infix = infix + ')';
		counterKlammerclose++;
		rightInfix = false;
		if (debugg)
		{
			std::cout << "Klammer zu wenig: " << infix << endl; //Test
		}
	}
	while (counterKlammerclose > counterKlammeropen) // Klammer ( zu wenig
	{
		infix = '(' + infix;
		counterKlammeropen++;
		rightInfix = false;
		if (debugg)
		{
			std::cout << "Klammer zu wenig: " << infix << endl; //Test
		}
	}

	if (infix == "")
	{
		throw (OwnException("\n Error: Empty Input \n \n"));
	}

	if (debugg) {
		msg = QString::fromStdString("= > Root Infix : " + infix);
		qDebug() << msg;
	}
	infix = checkRoot(infix);
	rightInfix = false; //Test

	if (!rightInfix) {
		msg = QString::fromStdString("= > Korrigierter Infix : " + infix);
		qDebug() << msg;
	}

	if (debugg) {
		msg = QString::fromStdString("= > Infix : " + infix);
		qDebug() << msg;
		qDebug() << "";
		qDebug() << "-------------------------------------------------";
	}
	return infix;
}