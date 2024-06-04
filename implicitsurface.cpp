#include "implicitsurface.h"
#include "interval.h"

bool ImplicitSurface::Intersect(const Vector& origin, const Vector& direction, double& t) const
{
   
    return false;
}

Vector ImplicitSurface::GetNormal(const Vector& point) const
{
    double epsilon = 1e-6;
    double dx = (Evaluate(point + Vector(epsilon, 0, 0)) - Evaluate(point - Vector(epsilon, 0, 0))) / (2 * epsilon);
    double dy = (Evaluate(point + Vector(0, epsilon, 0)) - Evaluate(point - Vector(0, epsilon, 0))) / (2 * epsilon);
    double dz = (Evaluate(point + Vector(0, 0, epsilon)) - Evaluate(point - Vector(0, 0, epsilon))) / (2 * epsilon);

    return Vector(dx, dy, dz).Normalization();
}

double ImplicitSurface::Evaluate(const Vector& point) const
{
    return func(point.x, point.y, point.z);
}