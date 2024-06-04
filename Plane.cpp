#include "plane.h"

bool Plane::Intersect(const Vector& Origin, const Vector& Direction, double& t) const
{
	double denom = n.DotProduct(Direction);
	if (n.DotProduct(Direction) != 0)
	{
		t = (p - Origin).DotProduct(n) / Direction.DotProduct(n);
		return true;
	}
	return false;
}