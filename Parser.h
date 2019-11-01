#pragma once

#include <sstream>
#include <string>
#include <cctype>
#include <algorithm>
#include <iostream>

class Parser
{
public:
	Parser(std::string str);
	~Parser();

	std::stringstream stream;

	void formatWhitespaces(std::string str);

	struct STerms
	{
		float	coef;
		int		degree;
	};

	bool isTrue = true;

	bool readTerms(STerms &result);

private:

	bool leftSide = true;

	bool sign = true;

	bool isInt(const std::string & str) const;

	bool isFloat(const std::string & str) const;

	bool isX(const std::string & str) const;

	bool getRootPart(std::string &str, STerms &result);

	bool processSigns(std::string &str);
};

