#pragma once
#ifndef __CONTEXT_H__
#define __CONTEXT_H__

#include "vector.h"
#include "matrix.h"
#include "triangle.h"
#include "ball.h"

class Context
{
public:
	Context(Triangle triangle, const Vector& o, const Vector& v1, const Vector& v2);

	void Init();	//������ �信 ���� �Լ�

private:
	void IsRayContact(bool flag, int index);	//���� �ﰢ�� �ȿ� �ִ��� ����ϴ� �Լ�

	Triangle triangle;
	Vector o, v1, v2;
	double t1, t2;
};

#endif // !__CONTEXT_H__
