#include "context.h"
#include "interval.h"
#include <cmath>
#include <limits>
#include <memory>
#include <iostream>

std::shared_ptr<Context> Context::context = nullptr;

Context::Context() {}

std::shared_ptr<Context> Context::GetContext()
{
	if (!context)
	{
		context = std::shared_ptr<Context>(new Context());
	}
	return std::move(context);
}

void Context::Init(const int& nx, const int& ny)
{
	FrameBuffer.resize(nx * ny);

	const double M_PI = 3.141592653589793238462643383279;

	double fov = 90;
	Vector E = { 600, 0, 0, 1 }; // ī�޶� ��ġ
	Vector D = { 0, 0, 0 }; // ī�޶� �ٶ󺸴� ����
	Vector AT = D - E;
	Vector UP = { 0, 0, 1 }; // �� ����
	Vector LightPos = { 300, 300, 300 };

	

	std::vector<Shape*> shapes = {
		//new Ball({0, 0, 0}, 50, {1, 0, 0}), // ������ ��
		//new Ball({0, 100, 0}, 50, {0, 1, 0}), // �ʷϻ� ��
		new Plane({1, 0, 0}, {0, 0, 0}, {0.2, 0.5, 0.8}), // ��� �ٴ�
		new ImplicitSurface({{0,-150,-100}, { 0,150,-100 }, {0,150,100}, {0,-150,100}}, 1.0, {1, 1, 0})
	};

	Vector U = AT * UP;
	Vector V = U * AT;
	Vector W = -AT;

	Matrix mat4;
	mat4.InitM({ U, V, W, E });
	double Distance = ny / (2 * tan(fov * M_PI / 360.0));


	for (int j = 0; j < ny; ++j)
	{
		for (int i = 0; i < nx; ++i)
		{
			Vector Pixel = { -(nx / 2.0) + (0.5 + (i * 1)), (ny / 2.0) - (0.5 + (j * 1)) ,  -Distance, 1 };
			Vector CameraToScreen = (mat4 * Pixel - E);
			Ray ray = { E, CameraToScreen };
			FrameBuffer[j * nx + i] = ray.TraceRay(shapes, LightPos);
		}
	}

	for (auto shape : shapes)
	{
		delete shape;
	}
}

std::vector<Color>& Context::GetFrameBuffer()
{
	return FrameBuffer;
}

Context::~Context()
{
	if (context)
	{
		context.reset();
	}
}


