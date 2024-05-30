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


class Context
{
public:
	static std::shared_ptr<Context> GetContext();
	void Init(const int& nx, const int& ny);
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
