// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <vector>
#include "Parser.h"
#include "Polynom.h"

int main(int c, char **v)
{
	std::string str = "5 * X^0 + 4 * X^1 - 9.3 * X^2 = 1 * X^0";
	Parser parser(str);
	Polynom polynom;
	Parser::STerms terms;
	while (parser.readTerms(terms))
		polynom.addCoef(terms.coef, terms.degree);
	std::cout << polynom << std::endl;
	std::cout << "Polynomial degree : " << polynom.getDegree() << std::endl;
	polynom.streamRoots(std::cout);
	std::cout << std::endl;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
