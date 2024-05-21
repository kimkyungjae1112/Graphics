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

	void Init();	//문제의 답에 대한 함수

private:
	void IsRayContact(bool flag, int index);	//점이 삼각형 안에 있는지 출력하는 함수

	Triangle triangle;
	Vector o, v1, v2;
	double t1, t2;
};

#endif // !__CONTEXT_H__
