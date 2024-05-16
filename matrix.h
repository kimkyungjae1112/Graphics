#pragma once
#ifndef __MATRIX_H__
#define __MATRIX_H__

#include "vector.h"
#include <vector>
class Matrix
{
public:
	Matrix();
	Matrix(float diagonal);
	~Matrix();
	static Matrix Identity();

	void InitM(std::vector<Vector> vectors);
	Vector operator*(const Vector& vector);

	void println();


private:
	float** mat4;

};


#endif // !__MATRIX_H__
