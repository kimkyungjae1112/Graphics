#pragma once
#ifndef __VECTOR_H__
#define __VECTOR_H__

class Vector
{
public:
    float x, y, z, w;

    Vector();
    Vector(float x_, float y_, float z_, float w_ = 0);


    Vector Normalization() const;   //���� ����ȭ
    float DotProduct(const Vector& vector) const;  //���� ����

    void println() const;   //���� ��� ���
    float SizeVector() const;  //���� ũ�� ���

    Vector operator+(const Vector& vector) const;
    Vector operator-(const Vector& vector) const;
    Vector operator-() const;
    Vector operator*(const Vector& vector) const; //���� ����
    Vector& operator*(float value);
    Vector& operator/(float value);
};

#endif //__VECTOR_H__