// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <vector>
#include "Parser.h"
#include "Polynom.h"

int main(int c, char **v)
{
	if (c != 2)
	{
		std::cout << "Wrong number of arguments\n";
		return 1;
	}
	Parser parser(v[1]);
	Polynom polynom;
	Parser::STerms terms;
	while (parser.readTerms(terms))
		polynom.addCoef(terms.coef, terms.degree);
	std::cout << polynom << std::endl;
	std::cout << "Polynomial degree : " << polynom.getDegree() << std::endl;
	polynom.streamRoots(std::cout);
	std::cout << std::endl;
}

