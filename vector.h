#pragma once
#ifndef __VECTOR_H__
#define __VECTOR_H__

class Vector
{
public:
    float x, y, z, w;

    Vector();
    Vector(float x_, float y_, float z_, float w_ = 0);


    Vector Normalization() const;   //벡터 정규화
    float DotProduct(const Vector& vector) const;  //벡터 내적

    void println() const;   //벡터 요소 출력
    float SizeVector() const;  //벡터 크기 출력

    Vector operator+(const Vector& vector) const;
    Vector operator-(const Vector& vector) const;
    Vector operator-() const;
    Vector operator*(const Vector& vector) const; //벡터 외적
    Vector& operator*(float value);
    Vector& operator/(float value);
};

#endif //__VECTOR_H__