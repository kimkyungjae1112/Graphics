#pragma once
#ifndef __RAY_H__
#define __RAY_H__

#include "vector.h"
#include "shape.h"
#include <vector>

class Ray
{
public:
    Ray(const Vector& origin, const Vector& direction);

    Color TraceRay(const std::vector<Shape*>& shapes, const Vector& lightPos);

private:
    Vector origin;
    Vector direction;

    bool IsInShadow(const Vector& point, const Vector& lightPos, const std::vector<Shape*>& shapes);
};

#endif // __RAY_H__