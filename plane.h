#pragma once
#ifndef __PLANE_H__
#define __PLANE_H__
#include "vector.h"

class Plane
{
public:
	Plane(const Vector& Normal, const Vector& Point, const Color& color);

	bool IsPlaneMeet(const Vector& o, double& t, const Vector& v) const;	//�ﰢ���� ������ ��鿡 ������ ��Ҵ��� Ȯ���ϴ� �Լ�

	Vector Normal;
	Vector Point;
	Color color;
};

#endif // !__PLANE_H__
