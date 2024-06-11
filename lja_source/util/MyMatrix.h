//201986 소프트웨어공학과 이장안
//3차원 동차 좌표계상의 행렬 및 벡터 클래스를 정의한다.

#pragma once
#ifndef __MY_MATRIX_H__
#define __MY_MATRIX_H__

#include <iostream>
#include <vector>
#include <initializer_list>


//벡터의 정의
namespace jangan_lee_my_matrix {

	class Matrix4d; //벡터 정의 위한 미리 선언

	//3차원 homogeneous 벡터를 표현하는 클래스
	//벡터, 점이 가능함
	class Vector4d {

	protected:
		static const int ROW = 4; //행의 수 = 4로 고정
		std::vector<std::vector<double>> _col; //동차 3차원 열벡터의 모음(4*n 행렬) 
		int _col_size; //열 개수
		Vector4d(int col_size) : _col_size(col_size), _col(col_size, std::vector<double>(ROW)) {} //열 사이즈가 col_size인 영행렬 정의

	public:
		const static Vector4d zero_vector;
		const static Vector4d zero_point;

		Vector4d(bool is_vector = true); //영벡터 또는 원점 생성
		Vector4d(std::initializer_list<double> list); //initializer_list를 사용, 3차원 homogenous 벡터(점) 초기화
		Vector4d(const Vector4d& rhs); 		//복사 생성자
		Vector4d(Vector4d&& rhs) noexcept;	//이동 생성자
		Vector4d(const Matrix4d& rhs);

		double& operator[](int idx);					//원소 참조 연산		
		std::vector<double>& col(int idx = 0) const;	//열벡터 참조 연산
		bool operator==(const Vector4d& rhs) const;		//동등 연산
		bool operator!=(const Vector4d& rhs) const;		//비동등 연산
		Vector4d operator*(double k) const;				//상수배 연산
		Vector4d operator/(double k) const;				//상수배 연산
		Vector4d operator-() const;						//부호 연산
		Vector4d operator+(const Vector4d& rhs) const;	//덧셈 연산
		Vector4d operator-(const Vector4d& rhs) const;	//뺄셈 연산
		Vector4d operator*(const Vector4d& rhs) const;	//외적 연산
		double dot(const Vector4d& rhs) const;			//내적 연산
		Vector4d point() const;		//객체를 점이라고 간주
		Vector4d vector() const;	//객체를 벡터라고 간주

		Vector4d& operator=(const Vector4d& rhs);		//대입 연산자
		Vector4d& operator=(Vector4d&& rhs) noexcept;	//이동 대입연산자
		friend std::ostream& operator<<(std::ostream& os, const Vector4d& m); //cout으로 간단히 출력(점인 경우 정규화된 3차원 좌표, 벡터인 경우 3차원 정보만 출력)
		std::string full_format() const; //현재 객체 정보를 모두 표현

		int col_size() const { return _col_size; } // 열 개수 얻기
		bool is_point() const; //객체가 점인지 확인
		bool is_vector() const; //객체가 벡터인지 확인
		double norm() const; //벡터의 크기(norm) 계산
		double cos(const Vector4d rhs) const; //주어진 벡터와의 각도의 cos값 계산
		Vector4d normalize() const; //정규화 수행(점인 경우 4번째 값을 1로 만듦, 벡터인 경우 크기를 1로 만듦)
		Matrix4d append(const Vector4d& rhs) const;	//두 행렬 덧붙이기
	};

	Vector4d operator*(double k, const Vector4d& m); //(교환법칙)행렬 스칼라배 연산
}


//행렬의 정의
namespace jangan_lee_my_matrix {

	//행이 4개인 4*n 3차원 homogeneous 행렬을 표현하는 클래스
	class Matrix4d : public Vector4d {
	public:
		Matrix4d(int col_size = ROW) : Vector4d(col_size) {} //열 사이즈가 col_size인 영행렬 정의
		Matrix4d(const Matrix4d& rhs) : Vector4d(rhs) {}				//복사 생성자
		Matrix4d(Matrix4d&& rhs) noexcept : Vector4d(std::move(rhs)) {}	//이동 생성자
		Matrix4d(const Vector4d& v1, const Vector4d& v2, const Vector4d& v3, const Vector4d& v4); //벡터 4개로 4*4 행렬 생성
		Matrix4d(std::initializer_list<std::vector<double>> list); //initializer_list를 사용, 구체값으로 n*4 행렬 초기화
		Matrix4d(const Vector4d& rhs); //Vector4d를 행렬로 변환

		std::vector<double>& operator[](int idx); //열벡터 참조 연산	
		bool operator==(const Matrix4d& rhs) const;		//동등 연산
		bool operator!=(const Matrix4d& rhs) const;		//비동등 연산	
		Matrix4d operator*(double k) const;				//스칼라배 연산
		Matrix4d operator/(double k) const;				//스칼라배 연산
		Matrix4d operator-() const;						//부호 연산
		Matrix4d operator+(const Matrix4d& rhs) const;	//행렬의 덧셈 연산(차원 일치하는 경우에만 수행)
		Matrix4d operator-(const Matrix4d& rhs) const;	//행렬의 뺄셈 연산(차원 일치하는 경우에만 수행)
		Matrix4d operator*(const Matrix4d& rhs) const;  //행렬곱 연산

		Matrix4d& operator=(const Matrix4d& rhs);		//대입연산자
		Matrix4d& operator=(Matrix4d&& rhs) noexcept;	//이동 대입연산자
		friend std::ostream& operator<<(std::ostream& os, const Matrix4d& m); //cout 출력

		int col_size() const { return _col_size; }	//열 개수 반환
		int row_size() const { return ROW; }		//행 개수 반환
	};

	Matrix4d operator*(double k, const Matrix4d& m); //(교환법칙)행렬 스칼라배 연산

}
#endif