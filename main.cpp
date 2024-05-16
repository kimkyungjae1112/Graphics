
#include "context.h"
#define PI 3.141592
int main()
{
	Vector E(0, 0, 0, 1);
	Vector D(1, 0, 0, 0);
	Vector UP(0, 0, 1, 0);

	Vector u = D * UP;
	Vector v = u * D;
	Vector w = -D;

	float nx = 100.0f;
	float ny = 100.0f;

	float fov = 90.0f * PI / 180.0f;	//90µµ
	float distance = ny / (2 * tan(fov / 2));

	Matrix mat4;
	mat4.InitM({ u, v, w, E });
	
	Vector PixelE = { (-nx + 1) / 2.0f, (ny - 1) / 2.0f, -distance, 1 };
	Vector PixelW = mat4 * PixelE;
	Vector PixelToVector = mat4 * PixelE - E;
	PixelToVector.println();

	Ball ball(Vector(-12.8f,0.0f,0.0f,1.0f), 12.0f, {1,0,0,1});
	float t;
	if (ball.FindRoot(E, PixelToVector, t))
	{
		printf("%f", t);
	}
	else
	{
		printf("æ»¥Í¿Ω %f", t);
	}

	return 0;
}
