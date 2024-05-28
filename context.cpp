#include "context.h"
#include <cmath>
#include <limits>

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
	Vector E = { 600, 0, 0, 1 }; // 카메라 위치
	Vector D = { 0, 0, 100 }; // 카메라가 바라보는 지점
	Vector AT = D - E;
	Vector UP = { 0, 0, 1 }; // 업 벡터
	Vector LightPos = { 300, 300, 300 };

	std::vector<Ball> Balls = {
		{{0, 0, 0}, 50, {1, 0, 0}}, // 빨간색 구
		{{0, 100, 0}, 50, {0, 1, 0}}, // 초록색 구
		{{100, 100, 100}, 50, {0,1,1}}
	};

	Plane floor = { {1, 0, 0}, {0, 0, 0}, {0.2, 0.5, 0.8} }; // 흰색 바닥

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
			FrameBuffer[j * nx + i] = ray.TraceRay(Balls, floor, LightPos);
		}
	}
}

double Context::IntervalMethod(const Interval& interval, Interval (*Function)(double, double))
{
	if (abs(interval.Bigger - interval.Smaller) < 1e-6) return (interval.Bigger + interval.Smaller) / 2.0;

	Interval J = Function(interval.Smaller, interval.Bigger);
	if (J.Smaller * J.Bigger > 0) return std::numeric_limits<double>::quiet_NaN();

	double Center = (interval.Bigger + interval.Smaller) / 2.0;
	Interval interval1 = { interval.Smaller, Center };
	Interval interval2 = { Center, interval.Bigger };

	double Root = IntervalMethod(interval1, Function);

	return !std::isnan(Root) ? Root : IntervalMethod(interval2, Function);	
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


