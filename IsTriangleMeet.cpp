#include "context.h"
#define PI 3.141592
int main()
{
	Vector p0(0, 0, 0, 1.0f);
	Vector p1(-1.0f, 5.0f, 0, 1.0f);
	Vector p2(1.0f, 0, 5.0f, 1.0f);

	Vector o(5.0f, 1.0f, 1.0f, 1.0f);

	Vector v1(-1.0f, 0.0f, 0.0f);
	Vector v2(-1.0f, 1.0f, 1.0f);

	Triangle triangle(p0, p1, p2);

	printf("[ Problem 1 ]\n(1) ");
	triangle.printN();

	Vector u_hat = triangle.FinduHat();
	Vector v_hat = triangle.FindvHat();
	printf("(2) ");
	u_hat.println();
	printf("(3) ");
	v_hat.println();


	printf("\n\n[ Problem 2 ]\n");
	Context context(triangle, o, v1, v2);
	context.Init();

	return 0;
}