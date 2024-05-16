#pragma once
#ifndef __PLANE_H__
#define __PLANE_H__
#include "vector.h"

class Plane
{
public:
	bool IsPlaneMeet(const Vector& o, float& t, const Vector& v);	//�ﰢ���� ������ ��鿡 ������ ��Ҵ��� Ȯ���ϴ� �Լ�

	Plane(const Vector& Normal, const Vector& Point, const Vector& Color);

private:
	Vector Normal;
	Vector Point;
	Vector Color;
};

#endif // !__PLANE_H__
