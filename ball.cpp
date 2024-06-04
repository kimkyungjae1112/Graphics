#include "ball.h"
#include <cmath>

bool Ball::Intersect(const Vector& origin, const Vector& direction, double& t) const
{
    Vector oc = origin - c;
    double a = direction.DotProduct(direction);
    double b = 2.0 * oc.DotProduct(direction);
    double c = oc.DotProduct(oc) - r * r;
    double D = b * b - 4 * a * c;
    if (D < 0) return false;
    else
    {
        t = (-b - sqrt(D)) / (2.0 * a);
        return true;
    }
}

Vector Ball::GetNormal(const Vector& point) const
{
    return (point - c).Normalization();
}