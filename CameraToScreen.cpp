#include "vector.h"
#include "matrix.h"
#define PI 3.141592
int main()
{
	Vector E(5, 1, 1, 1);
	Vector D(-5, -1, -1, 0);
	Vector UP(0, 1, 0, 0);

	Vector u = D * UP;
	Vector v = u * D;
	Vector w = -D;

	double nx = 100;
	double ny = 100;

	double fov = 90 * PI / 180;	//90도
	double distance = ny / (2 * tan(fov / 2));

	//1. u, v, w 단위벡터
	printf("u 단위 벡터 : ");
	u.Normalization().println();

	printf("v 단위 벡터 : ");
	v.Normalization().println();

	printf("w 단위 벡터 : ");
	w.Normalization().println();

	printf("\n");

	Matrix mat4;
	mat4.InitM({ u, v, w, E });
	printf("M 행렬\n");
	mat4.println();
	Vector p_first = { (-nx + 1) / 2.0, (ny - 1) / 2.0, -distance, 1 };
	Vector v_first = mat4 * p_first - E;

	Vector p_last = { (nx - 1) / 2.0, (-ny + 1) / 2.0, -distance, 1 };
	Vector v_last = mat4 * p_last - E;

	printf("\npixel의 첫번째, 두번째 좌표\n");
	p_first.println();
	p_last.println();

	//2. 첫번재 픽셀과 마지막 픽셀로 향하는 v1, v2 벡터
	printf("\nfirst pixel로 향하는 벡터 : ");
	v_first.println();

	printf("last pixel로 향하는 벡터 : ");
	v_last.println();

}