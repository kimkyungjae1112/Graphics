#pragma once
#ifndef __PLANE_H__
#define __PLANE_H__
#include "vector.h"

class Plane
{
public:
	bool IsPlaneMeet(const Vector& o, float& t, const Vector& v);	//삼각형을 포함한 평면에 광선이 닿았는지 확인하는 함수

	Plane(const Vector& Normal, const Vector& Point, const Vector& Color);

private:
	Vector Normal;
	Vector Point;
	Vector Color;
};

#endif // !__PLANE_H__
