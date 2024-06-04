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
//	bool IsTriangleMeet(const Vector& o, double& t, const Vector& v, const Vector& p);	//삼각형 안에 점이 있는지 확인하는 함수
//	Vector FinduHat();	//상수 u 값을 찾기 위한 함수
//	Vector FindvHat();	//상수 v 값을 찾기 위한 함수
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