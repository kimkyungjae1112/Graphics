#pragma once
#ifndef __IMPLICITSURFACE_H__
#define __IMPLICITSURFACE_H__

#include "shape.h"
#include "interval.h"
#include <functional>

class ImplicitSurface : public Shape
{
public:
    ImplicitSurface(std::function<double(double, double, double)> implicitFunc, const Color& color)
        : func(implicitFunc), col(color)
    {
    }

    virtual bool Intersect(const Vector& origin, const Vector& direction, double& t) const override;
    virtual Vector GetNormal(const Vector& point) const override;
    virtual Color GetColor() const override { return col; }

private:
    std::function<double(double, double, double)> func;
    Color col;

    double Evaluate(const Vector& point) const;
};

#endif // __IMPLICITSURFACE_H__