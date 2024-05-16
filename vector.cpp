#include "vector.h"
#include <stdio.h>
#include <cmath>

Vector::Vector() : x(0), y(0), z(0), w(1) {}
Vector::Vector(float x_, float y_, float z_, float w_) : x(x_), y(y_), z(z_), w(w_) {}

Vector Vector::Normalization() const
{
    float size = SizeVector();
    return Vector(x / size, y / size, z / size);
}

float Vector::DotProduct(const Vector& vector) const
{
    return x * vector.x + y * vector.y + z * vector.z;
}

void Vector::println() const
{
    printf("[%0.5f, %0.5f, %0.5f]\n", x, y, z);
}

float Vector::SizeVector() const
{
    return sqrt(x * x + y * y + z * z);
}

Vector Vector::operator+(const Vector& vector) const
{
    return Vector(x + vector.x, y + vector.y, z + vector.z);
}

Vector Vector::operator-(const Vector& vector) const
{
    return Vector(x - vector.x, y - vector.y, z - vector.z, 0);
}

Vector Vector::operator-() const
{
    return Vector(-x, -y, -z, 0);
}

Vector Vector::operator*(const Vector& vector) const
{
    return Vector(y * vector.z - z * vector.y,
        z * vector.x - x * vector.z,
        x * vector.y - y * vector.x,
        0
    );
}

Vector& Vector::operator*(float value)
{
    x = x * value;
    y = y * value;
    z = z * value;
    return *this;
}

Vector& Vector::operator/(float value)
{
    x = x / value;
    y = y / value;
    z = z / value;
    return *this;
}