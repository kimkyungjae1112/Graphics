#pragma once
#ifndef __SHAPE_H__
#define __SHAPE_H__

#include "vector.h"

class Shape
{
public:
    virtual ~Shape() {}
    virtual bool Intersect(const Vector& origin, const Vector& direction, double& t) const = 0;
    virtual Vector GetNormal(const Vector& point) const = 0;
    virtual Color GetColor() const = 0;
};

#endif // __SHAPE_H__