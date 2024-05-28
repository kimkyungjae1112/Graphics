#pragma once
#ifndef __BALL_H__
#define __BALL_H__

#include "vector.h"

class Ball
{
public:
	Ball(const Vector& c, const double& r, const Color& color);
	bool FindRoot(const Vector& o, const Vector& v, double& t) const;

	Vector c;
	double r;
	Color color;
};


#endif // !__BALL_H__
