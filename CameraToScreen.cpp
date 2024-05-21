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

	double fov = 90 * PI / 180;	//90��
	double distance = ny / (2 * tan(fov / 2));

	//1. u, v, w ��������
	printf("u ���� ���� : ");
	u.Normalization().println();

	printf("v ���� ���� : ");
	v.Normalization().println();

	printf("w ���� ���� : ");
	w.Normalization().println();

	printf("\n");

	Matrix mat4;
	mat4.InitM({ u, v, w, E });
	printf("M ���\n");
	mat4.println();
	Vector p_first = { (-nx + 1) / 2.0, (ny - 1) / 2.0, -distance, 1 };
	Vector v_first = mat4 * p_first - E;

	Vector p_last = { (nx - 1) / 2.0, (-ny + 1) / 2.0, -distance, 1 };
	Vector v_last = mat4 * p_last - E;

	printf("\npixel�� ù��°, �ι�° ��ǥ\n");
	p_first.println();
	p_last.println();

	//2. ù���� �ȼ��� ������ �ȼ��� ���ϴ� v1, v2 ����
	printf("\nfirst pixel�� ���ϴ� ���� : ");
	v_first.println();

	printf("last pixel�� ���ϴ� ���� : ");
	v_last.println();

}