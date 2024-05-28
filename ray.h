#pragma once
#ifndef __RAY_H__
#define __RAY_H__

#include "vector.h"
#include "ball.h"
#include "plane.h"
#include <vector>

class Ray
{
public:
	Ray(const Vector& InOrigin, const Vector& InDirection);
	
	Vector GetDirection() const { return Direction; } 

	bool IsInShadow(const Vector& Point, const Vector& LightPos, const std::vector<Ball>& Balls, const Plane& Floor);

	Color TraceRay(const std::vector<Ball>& Balls, const Plane& Floor, const Vector& LightPos);

private:
	Vector Origin;
	Vector Direction;
};

#endif //__RAY_H__