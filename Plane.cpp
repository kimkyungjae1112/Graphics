#include "plane.h"

Plane::Plane(const Vector& Normal, const Vector& Point, const Vector& Color) : Normal(Normal), Point(Point), Color(Color)
{

}

bool Plane::IsPlaneMeet(const Vector& o, float& t, const Vector& v)
{
	if (v.DotProduct(Normal) != 0)
	{
		t = (Point - o).DotProduct(Normal) / v.DotProduct(Normal);
		return true;
	}
	return false;
}