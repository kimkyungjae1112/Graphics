#pragma once
#ifndef __PLANE_H__
#define __PLANE_H__
#include "vector.h"

class Plane
{
public:
	Plane(const Vector& Normal, const Vector& Point, const Color& color);

	bool IsPlaneMeet(const Vector& o, double& t, const Vector& v) const;	//삼각형을 포함한 평면에 광선이 닿았는지 확인하는 함수

	Vector Normal;
	Vector Point;
	Color color;
};

#endif // !__PLANE_H__
