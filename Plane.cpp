#include "plane.h"

Plane::Plane(const Vector& Normal, const Vector& Point, const Color& color) : Normal(Normal), Point(Point), color(color)
{

}

bool Plane::IsPlaneMeet(const Vector& o, double& t, const Vector& v) const
{
	if (v.DotProduct(Normal) != 0)
	{
		t = (Point - o).DotProduct(Normal) / v.DotProduct(Normal);
		return true;
	}
	return false;
}