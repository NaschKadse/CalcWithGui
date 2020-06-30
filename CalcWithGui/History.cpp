#include "History.h"
#include <string>
#include <vector>

std::vector <string> H_infix;
std::vector <double> H_result;


History::History(string infix, double result) : m_infix(infix), m_result(result)
{

}
History::History(int index) : m_index(index)
{

}
History::~History()
{

}

void History::writeHistory(string m_infix, double  m_result) {
	H_infix.push_back(m_infix);
	H_result.push_back(m_result);
}

string History::outputInfix(int m_index) {
	return H_infix.at(m_index);
}

double History::outputResult(int m_index) {
	return H_result.at(m_index);
}