#include "ball.h"
#include <cmath>
#include <stdio.h>
#include <limits>
#include <algorithm>

Ball::Ball(const Vector& c, const double& r, const Color& color) : c(c), r(r), color(color)
{

}

bool Ball::FindRoot(const Vector& o, const Vector& v, double& t) const	//ball과 ray와의 hit 여부, 즉 근이 있는지 없는지 검사하는 함수
{
	double A = v.DotProduct(v);
	double B = v.DotProduct(o - c);	//짝수 근의 방정식의 공식으로 b의 절반값의 제곱
	double VarC = (o - c).DotProduct(o - c) - (r * r);
	double D = (B * B) - A * VarC;


	if (D > 0)	//ray가 ball을 관통한다면
	{
		t = (- B - sqrt(D)) / A;
		return true;
	}
	else
	{
		return false;
	}
}
