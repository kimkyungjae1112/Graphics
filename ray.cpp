#include "ray.h"

Ray::Ray(const Vector& InOrigin, const Vector& InDirection) : Origin(InOrigin), Direction(InDirection)
{
}

bool Ray::IsInShadow(const Vector& Point, const Vector& LightPos, const std::vector<Ball>& Balls, const Plane& Floor)
{
	const Vector LightDir = (LightPos - Point).Normalization();

	for (const auto& ball : Balls)
	{
		double t;
		if (ball.FindRoot(Point, LightDir, t) && t > 1e-6)
		{
			return true;
		}
	}

	double FloorT;
	if (Floor.IsPlaneMeet(Point, FloorT, LightDir) && FloorT > 1e-6)
	{
		return true;
	}

	return false;
}
 

Color Ray::TraceRay(const std::vector<Ball>& Balls, const Plane& Floor, const Vector& LightPos)
{
	Color BackGround = { 1.0, 1.0, 1.0 };
	Color color = BackGround;

	for (const auto& ball : Balls)
	{
		double t = 0;
		if (ball.FindRoot(Origin, Direction, t))
		{
			Vector HitPoint = Origin + Direction * t;
			Vector Normal = (HitPoint - ball.c).Normalization();
			Vector LightDir = (LightPos - HitPoint).Normalization();
			double Intensity = std::max(0.0, Normal.DotProduct(LightDir));
			if (IsInShadow(HitPoint, LightPos, Balls, Floor))
			{
				Intensity *= 0.5;
			}
			color = ball.color * Intensity;
			return color;
		}
	}
	
	double FloorT = 0;
	if (Floor.IsPlaneMeet(Origin, FloorT, Direction))
	{
		Vector HitPoint = Origin + Direction * FloorT;
		Vector LightDir = (LightPos - HitPoint).Normalization();
		double Intensity = std::max(0.0, Floor.Normal.DotProduct(LightDir));
		if (IsInShadow(HitPoint, LightPos, Balls, Floor))
		{
			Intensity *= 0.5;
		}
		color = Floor.color * Intensity;
		return color;
	}
	
	return color;
}
