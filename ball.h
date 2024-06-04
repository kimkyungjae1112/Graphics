#pragma once
#ifndef __BALL_H__
#define __BALL_H__

#include "shape.h"

class Ball : public Shape
{
public:
    Ball(const Vector& center, double radius, const Color& color)
        : c(center), r(radius), col(color)
    {
    }

    virtual bool Intersect(const Vector& origin, const Vector& direction, double& t) const override;
    virtual Vector GetNormal(const Vector& point) const override;
    virtual Color GetColor() const override { return col; }

private:
    Vector c; // center
    double r; // radius
    Color col;
};

#endif // __BALL_H__