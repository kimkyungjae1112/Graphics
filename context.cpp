#include "context.h"

Context::Context(Triangle triangle, const Vector& o, const Vector& v1, const Vector& v2) :
	triangle(triangle), o(o), v1(v1), v2(v2)
{
	triangle.IsPlaneMeet(o, t1, v1);
	triangle.IsPlaneMeet(o, t2, v2);
}

void Context::Init()
{
	Vector v1_p = o + v1 * t1;
	Vector v2_p = o + v2 * t2;

	printf("교차점 P");
	v1_p.println();
	printf("t : %f\n", t1);
	IsRayContact(triangle.IsTriangleMeet(o, t1, v1, v1_p), 1);

	printf("교차점 P");
	v2_p.println();
	printf("t : %f\n", t2);
	IsRayContact(triangle.IsTriangleMeet(o, t2, v2, v2_p), 2);
}

void Context::IsRayContact(bool flag, int index)
{
	if (flag)
	{
		printf("v%d와 삼각형의 교차 여부: YES\n\n", index);
	}
	else
	{
		printf("v%d와 삼각형의 교차 여부: NO\n\n", index);
	}
}