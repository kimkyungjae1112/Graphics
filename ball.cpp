#include "ball.h"
#include <cmath>
#include <stdio.h>
#include <limits>
#include <algorithm>

Ball::Ball(const Vector& c, const double& r, const Color& color) : c(c), r(r), color(color)
{

}

bool Ball::FindRoot(const Vector& o, const Vector& v, double& t) const	//ball�� ray���� hit ����, �� ���� �ִ��� ������ �˻��ϴ� �Լ�
{
	double A = v.DotProduct(v);
	double B = v.DotProduct(o - c);	//¦�� ���� �������� �������� b�� ���ݰ��� ����
	double VarC = (o - c).DotProduct(o - c) - (r * r);
	double D = (B * B) - A * VarC;


	if (D > 0)	//ray�� ball�� �����Ѵٸ�
	{
		t = (- B - sqrt(D)) / A;
		return true;
	}
	else
	{
		return false;
	}
}
