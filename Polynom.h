#pragma once

#include <cmath>
#include <iostream>
#include <map>

class Polynom
{
public:
	Polynom();
	~Polynom();

	bool	addCoef(float coef, int degree);
	float	getDiscriminant();
	bool	getRoots(float &x1, float &x2);

	std::map<int,float> coefs;

	void	streamRoots(std::ostream& out);
	int		getDegree();

private:

	int  minDegree = 0;

	bool getRoots1(float &x1, float &x2);
	bool getRoots2(float &x1, float &x2);
};

std::ostream& operator<<(std::ostream& out, const Polynom& f);

