#include "ball.h"
#include <cmath>

Ball::Ball(const Vector& c, const float& r, const Vector& Color) : c(c), r(r), Color(Color)
{

}

bool Ball::FindRoot(Vector& o, Vector& v, float& t)	//ball과 ray와의 hit 여부, 즉 근이 있는지 없는지 검사하는 함수
{
	float A = v.DotProduct(v);
	float B = v.DotProduct(o - c) / 2;	//짝수 근의 방정식의 공식으로 b의 절반값의 제곱
	float VarC = (o - c).DotProduct(o - c) - (r * r);
	float D = (B * B) - A * VarC;


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

