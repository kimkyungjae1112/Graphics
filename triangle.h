//#pragma once
//#ifndef __TRIANGLE_H__
//#define __TRIANGLE_H__
//#include "vector.h"
//#include "plane.h"
//
//class Triangle : public Plane
//{
//public:
//	Triangle(const Vector& point0, const Vector& point1, const Vector& point2);
//
//	bool IsTriangleMeet(const Vector& o, double& t, const Vector& v, const Vector& p);	//�ﰢ�� �ȿ� ���� �ִ��� Ȯ���ϴ� �Լ�
//	Vector FinduHat();	//��� u ���� ã�� ���� �Լ�
//	Vector FindvHat();	//��� v ���� ã�� ���� �Լ�
//
//	void printN();
//
//private:
//	Vector Edge(const Vector& p1, const Vector& p2) const;
//	Vector MakeNormalVector(const Vector& p1, const Vector& p2) const;
//
//	Vector point0, point1, point2;
//};
//
//#endif //__TRIANGLE_H__