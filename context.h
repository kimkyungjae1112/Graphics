#pragma once
#ifndef __CONTEXT_H__
#define __CONTEXT_H__

#include "vector.h"
#include "matrix.h"
#include "triangle.h"
#include "ball.h"
#include "ray.h"
#include <vector>
#include <memory>

struct Interval
{
	double Smaller;
	double Bigger;

	Interval operator*(const Interval& interval)
	{
		double a = Smaller * interval.Smaller;
		double b = Smaller * interval.Bigger;
		double c = Bigger * interval.Smaller;
		double d = Bigger * interval.Bigger;

		return { std::min({a, b, c, d}), std::max({a, b, c, d}) };
	}

	Interval operator+(const Interval& interval)
	{
		return { Smaller + interval.Smaller, Bigger + interval.Bigger };
	}
			
};

class Context
{
public:
	static std::shared_ptr<Context> GetContext();
	void Init(const int& nx, const int& ny);
	
	double IntervalMethod(const Interval& interval, Interval (*Function)(double, double));


	std::vector<Color>& GetFrameBuffer();
	~Context();

private:
	static std::shared_ptr<Context> context;
	std::vector<Color> FrameBuffer;

	Context();
	Context(const Context&) = delete;
	Context operator=(const Context&) = delete;
};

#endif // !__CONTEXT_H__
