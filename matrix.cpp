#include "matrix.h"

Matrix::Matrix() : mat4(new double* [4])
{
	for (int i = 0; i < 4; ++i)
	{
		mat4[i] = new double[4];
	}
}

Matrix::Matrix(double diagonal) : Matrix()
{
	mat4[0][0] = diagonal;
	mat4[1][1] = diagonal;
	mat4[2][2] = diagonal;
	mat4[3][3] = diagonal;
}

Matrix::~Matrix()
{
	for (int i = 0; i < 4; ++i)
	{
		delete[] mat4[i];
	}
	delete mat4;
}

void Matrix::InitM(std::vector<Vector> vectors)
{

	mat4[0][0] = vectors[0].x / vectors[0].SizeVector();
	mat4[1][0] = vectors[0].y / vectors[0].SizeVector();
	mat4[2][0] = vectors[0].z / vectors[0].SizeVector();
	mat4[3][0] = vectors[0].w;


	mat4[0][1] = vectors[1].x / vectors[1].SizeVector();
	mat4[1][1] = vectors[1].y / vectors[1].SizeVector();
	mat4[2][1] = vectors[1].z / vectors[1].SizeVector();
	mat4[3][1] = vectors[1].w;

	mat4[0][2] = vectors[2].x / vectors[2].SizeVector();
	mat4[1][2] = vectors[2].y / vectors[2].SizeVector();
	mat4[2][2] = vectors[2].z / vectors[2].SizeVector();
	mat4[3][2] = vectors[2].w;


	mat4[0][3] = vectors[3].x;
	mat4[1][3] = vectors[3].y;
	mat4[2][3] = vectors[3].z;
	mat4[3][3] = vectors[3].w;
}

Vector Matrix::operator*(const Vector& vector)
{
	return Vector(mat4[0][0] * vector.x + mat4[0][1] * vector.y + mat4[0][2] * vector.z + mat4[0][3] * vector.w,
		mat4[1][0] * vector.x + mat4[1][1] * vector.y + mat4[1][2] * vector.z + mat4[1][3] * vector.w,
		mat4[2][0] * vector.x + mat4[2][1] * vector.y + mat4[2][2] * vector.z + mat4[2][3] * vector.w,
		mat4[3][0] * vector.x + mat4[3][1] * vector.y + mat4[3][2] * vector.z + mat4[3][3] * vector.w
	);
}

Matrix Matrix::Identity()
{
	return Matrix(1.0f);
}

void Matrix::println()
{
	for (int i = 0; i < 4; ++i)
	{
		printf("[ ");
		for (int j = 0; j < 4; ++j)
		{
			printf("%0.7lf ", mat4[i][j]);
		}
		printf(" ]\n");
	}
}