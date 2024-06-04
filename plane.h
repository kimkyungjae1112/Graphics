#pragma once
#ifndef __PLANE_H__
#define __PLANE_H__

#include "shape.h"

class Plane : public Shape
{
public:
    Plane(const Vector& normal, const Vector& point, const Color& color)
        : n(normal), p(point), col(color)
    {
    }

    virtual bool Intersect(const Vector& Origin, const Vector& Direction, double& t) const override;
    virtual Vector GetNormal(const Vector& Point) const override { return n; }
    virtual Color GetColor() const override { return col; }

private:
    Vector n; // normal
    Vector p; // point
    Color col;
};

#endif // __PLANE_H__