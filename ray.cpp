#include "ray.h"
#include <cmath>
#include <limits>
#include <iostream>

Ray::Ray(const Vector& origin, const Vector& direction)
    : origin(origin), direction(direction)
{
}

bool Ray::IsInShadow(const Vector& point, const Vector& lightPos, const std::vector<Shape*>& shapes)
{
    Vector lightDir = (lightPos - point).Normalization();

    for (const auto& shape : shapes)
    {
        double t;
        if (shape->Intersect(point, lightDir, t) && t > 1e-6)
        {
            return true;
        }
    }
    return false;
}

Color Ray::TraceRay(const std::vector<Shape*>& shapes, const Vector& lightPos)
{
    Color background = { 1.0, 1.0, 1.0 };
    Color color = background;
    double tMin = std::numeric_limits<double>::max();
    const Shape* hitShape = nullptr;
    Vector hitPoint;

    for (const auto& shape : shapes)
    {
        double t;
        if (shape->Intersect(origin, direction, t) && t < tMin)
        {
            tMin = t;
            hitShape = shape;
        }
    }

    if (hitShape)
    {
        hitPoint = origin + direction * tMin;
        Vector normal = hitShape->GetNormal(hitPoint);
        Vector lightDir = (lightPos - hitPoint).Normalization();
        double intensity = /*std::max(0.0, normal.DotProduct(lightDir))*/1.0;
        if (IsInShadow(hitPoint, lightPos, shapes))
        {
            intensity *= 0.5;
        }
        color = hitShape->GetColor() * intensity;
    }

    return color;
}