#include "triangle.h"
#include <stdio.h>

Triangle::Triangle(const Vector& point0, const Vector& point1, const Vector& point2) : 
	Plane(MakeNormalVector(Edge(point0, point1), Edge(point0, point2)), point0, {1, 0, 0}), point0(point0), point1(point1), point2(point2)
{
	
}

bool Triangle::IsTriangleMeet(const Vector& o, double& t, const Vector& v, const Vector& p)
{
	if (IsPlaneMeet(o, t, v))
	{
		float u = (p - point0).DotProduct(FinduHat());
		float v = (p - point0).DotProduct(FindvHat());
		printf("u : %f, f : %f\n", u, v);
		if (u + v < 1 && u > 0 && v > 0) return true;
	}
	return false;
}

Vector Triangle::FinduHat()
{
	Vector p0p1 = Edge(point0, point1);
	Vector p0p2 = Edge(point0, point2);
	Vector N = MakeNormalVector(p0p1, p0p2);

	float k = (p0p1 * p0p2).DotProduct(N);

	return (p0p2 * N) / k;
}

Vector Triangle::FindvHat()
{
	Vector p0p1 = Edge(point0, point1);
	Vector p0p2 = Edge(point0, point2);
	Vector N = MakeNormalVector(p0p1, p0p2);

	float k = (p0p1 * p0p2).DotProduct(N);

	return (N * p0p1) / k;
}

void Triangle::printN()
{
	Vector p0p1 = Edge(point0, point1);
	Vector p0p2 = Edge(point0, point2);
	Vector N = MakeNormalVector(p0p1, p0p2);

	N.println();
}

Vector Triangle::Edge(const Vector& p1, const Vector& p2) const
{
	return p2 - p1;
}

Vector Triangle::MakeNormalVector(const Vector& p1, const Vector& p2) const
{
	return p1 * p2;
}