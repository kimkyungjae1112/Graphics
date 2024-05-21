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


    Vector Normalization() const;   //���� ����ȭ
    double DotProduct(const Vector& vector) const;  //���� ����

    void println() const;   //���� ��� ���
    double SizeVector() const;  //���� ũ�� ���

    Vector operator+(const Vector& vector) const;
    Vector operator-(const Vector& vector) const;
    Vector operator-() const;
    Vector operator*(const Vector& vector) const; //���� ����
    Vector& operator*(double value);
    Vector& operator/(double value);
};

#endif //__VECTOR_H__