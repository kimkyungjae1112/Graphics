#pragma once
#ifndef __BALL_H__
#define __BALL_H__

#include "vector.h"

class Ball
{
public:
	Ball(const Vector& c, const float& r, const Vector& Color);

	bool FindRoot(Vector& o, Vector& v, float& t);

private:
	Vector c;
	float r;
	Vector Color;

};


#endif // !__BALL_H__
