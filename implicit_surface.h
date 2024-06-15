#pragma once
#ifndef __IMPLICIT_SURFACE_H__
#define __IMPLICIT_SURFACE_H__
#include "vector.h"
#include "shape.h"
#include <functional>
#include <vector>

class ImplicitSurface : public Shape
{
public:
    ImplicitSurface(const std::vector<Vector>& metaballs, double isoValue, const Color& color);
    bool Intersect(const Vector& origin, const Vector& direction, double& t) const;
    Vector GetNormal(const Vector& point) const;
    Color GetColor() const;

private:
    std::vector<Vector> metaballs;
    double isoValue;
    Color color;
};

#endif //__IMPLICIT_SURFACE_H__