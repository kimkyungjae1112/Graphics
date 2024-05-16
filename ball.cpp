#include "ball.h"
#include <cmath>

Ball::Ball(const Vector& c, const float& r, const Vector& Color) : c(c), r(r), Color(Color)
{

}

bool Ball::FindRoot(Vector& o, Vector& v, float& t)	//ball�� ray���� hit ����, �� ���� �ִ��� ������ �˻��ϴ� �Լ�
{
	float A = v.DotProduct(v);
	float B = v.DotProduct(o - c) / 2;	//¦�� ���� �������� �������� b�� ���ݰ��� ����
	float VarC = (o - c).DotProduct(o - c) - (r * r);
	float D = (B * B) - A * VarC;


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

