#include "pch.h"
#include "Parser.h"
#include <regex>


Parser::Parser(std::string str)
{
	stream = std::stringstream(str);
}

Parser::~Parser()
{
}

void Parser::formatWhitespaces(std::string str)
{
	str.erase(str.begin(), std::find_if(str.begin(), str.end(), [](int ch) {
			return !std::isspace(ch);
	}));
	str.erase(std::find_if(str.rbegin(), str.rend(), [](int ch) {
		return !std::isspace(ch);
	}).base(), str.end());
	std::replace(str.begin(), str.end(), '\t', ' ');
	std::replace(str.begin(), str.end(), '\v', ' ');
	std::replace(str.begin(), str.end(), '\r', ' ');
}

bool Parser::readTerms(STerms & result)
{
	//std::cout << std::endl << leftSide << " - " << sign << std::endl;
	std::string substr;
	if (stream.good())
		std::getline(stream, substr, ' ');
	else return false;
	result.coef = (sign ? 1.0f : -1.0f) * (leftSide ? 1.0f : -1.0f);
	result.degree = 0;
	if (isFloat(substr))
	{
		result.coef *= std::stof(substr);
		if (stream.good())
			std::getline(stream, substr, ' ');
		if (substr == "*")
		{
			if (stream.good())
				std::getline(stream, substr, ' ');
			getRootPart(substr, result);
		}
		else
			processSigns(substr);
		return true;
	}
	if (getRootPart(substr, result))
		return true;
	else
	{
		if (processSigns(substr))
			readTerms(result);
	}
	return true;
}

bool Parser::isInt(const std::string &str) const {
	return (std::regex_match(str, std::regex(R"(^[-]?[0-9]+$)")));
}

bool Parser::isFloat(const std::string &str) const {
	if (isInt(str))
		return true;
	return (std::regex_match(str, std::regex(R"(^[-]?[0-9]+\.[0-9]+$)")));
}

bool Parser::isX(const std::string & str) const
{
	if (str[0] == 'x' || str[0] == 'X')
		return true;
	return false;
}

bool Parser::getRootPart(std::string & str, STerms & result)
{
	//std::cout << "\n" << str << "\n";
	if (!isX(str))
		return false;
	if (str.length() > 2 && str[1] == '^')
	{
		str = str.substr(2, str.length());
		//std::cout << str << std::endl;
		result.degree = std::stoi(str);
	}
	else
		result.degree = 1;
	return true;
}

bool Parser::processSigns(std::string & str)
{
	if (str == "+")
		sign = true;
	else if (str == "-")
		sign = false;
	else if (str == "=")
	{
		if (!leftSide)
			return false;
		leftSide = false;
		sign = true;
	}
	else return false;
	return true;
}
