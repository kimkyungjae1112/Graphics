#pragma once
#ifndef __VECTOR_H__
#define __VECTOR_H__
#include <stdio.h>

struct Color
{
    double r, g, b;

    Color() {}
    Color(const double& r, const double& g, const double& b)
        : r(r), g(g), b(b)
    {

    }
    void println()
    {
        printf("%lf %lf %lf\n", r, g, b);
    }

    Color operator*(double value) const
    {
        return Color(r * value, g * value, b * value);
    }
};

class Vector
{
public:
    double x, y, z, w;

    Vector();
    Vector(double x_, double y_, double z_, double w_ = 0);


    Vector Normalization() const;   //벡터 정규화
    double DotProduct(const Vector& vector) const;  //벡터 내적

    void println() const;   //벡터 요소 출력
    double SizeVector() const;  //벡터 크기 출력

    Vector operator+(const Vector& vector) const;
    Vector operator-(const Vector& vector) const;
    Vector operator-() const;
    Vector operator*(const Vector& vector) const; //벡터 외적
    Vector& operator*(double value);
    Vector& operator/(double value);
};

#endif //__VECTOR_H__