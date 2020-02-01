#include "pch.h"
#include "Polynom.h"


Polynom::Polynom()
{
	coefs.insert(std::make_pair(0, 0));
	coefs.insert(std::make_pair(1, 0));
	coefs.insert(std::make_pair(2, 0));
}


Polynom::~Polynom()
{
}

bool Polynom::addCoef(float coef, int degree)
{
	if (!coefs.insert(std::make_pair(degree, coef)).second)
		coefs[degree] += coef;
	return true;

}

float Polynom::getDiscriminant()
{
	return coefs.at(1) * coefs.at(1) - 4 * coefs.at(2) * coefs.at(0);
}

bool Polynom::getRoots(float & x1, float & x2)
{
	int degree = getDegree();
	if (minDegree < 0)
		return false;
	if (degree == 1)
		return getRoots1(x1, x2);
	else if (degree == 2)
		return getRoots2(x1, x2);
	else
		return false;
}

void Polynom::streamRoots(std::ostream & out)
{
	float x1, x2;
	if (getRoots(x1, x2))
	{
		out << x1;
		if (x1 != x2)
			out << ", " << x2;
	}
	else
		out << "I can't solve";

}

int Polynom::getDegree()
{
	int degree = 0;
	minDegree = 0;
	for (std::pair<int, float> p : coefs)
	{
		if (p.second != 0)
			degree = degree > p.first ? degree : p.first;
		if (p.second != 0)
			minDegree = degree < p.first ? degree : p.first;
	}
	return degree;
}


bool Polynom::getRoots1(float & x1, float & x2)
{
	if (coefs.at(1) == 0)
		return false;
	x1 = - coefs.at(0) / coefs.at(1);
	x2 = x1;
	return true;
}


bool Polynom::getRoots2(float & x1, float & x2)
{
	float discriminant = getDiscriminant();
	if (discriminant < 0)
		return false;
	x1 = (-coefs.at(1) + psqrt(discriminant)) / (2 * coefs.at(2));
	x2 = (-coefs.at(1) - psqrt(discriminant)) / (2 * coefs.at(2));
	return true;
}

float psqrt(float value)
{
	float low = 0, hight = value, mid;
 	for (int i = 0 ; i < 1000 ; i++){
     	mid = (low + hight) / 2;
     	if (mid * mid == value)
     		return mid;
     	if (mid * mid > value)
     		hight = mid;
     	else
     		low = mid;
  }
  return mid;
}

float pabs(float value)
{
	return value > 0 ? value : -value;
}

std::ostream & operator<<(std::ostream & out, const Polynom & f)
{
	for (std::pair<int, float> p : f.coefs)
	{
		if (p.second != 0)
		{
			if (p.second > 0)
			{
				if (p.first != 0)
					out << " + ";
			}
			else
				out << " - ";
			if (pabs(p.second) != 1)
				out << pabs(p.second);
			if (p.first > 0)
			{
				if (pabs(p.second) != 1)
					out << " *";
				out << " X";
				if (p.first > 1)
					out << "^" << p.first;
			}
		}
	}
	out << " = 0";
	return out;
}
