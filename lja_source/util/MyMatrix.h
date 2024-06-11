//201986 ����Ʈ������а� �����
//3���� ���� ��ǥ����� ��� �� ���� Ŭ������ �����Ѵ�.

#pragma once
#ifndef __MY_MATRIX_H__
#define __MY_MATRIX_H__

#include <iostream>
#include <vector>
#include <initializer_list>


//������ ����
namespace jangan_lee_my_matrix {

	class Matrix4d; //���� ���� ���� �̸� ����

	//3���� homogeneous ���͸� ǥ���ϴ� Ŭ����
	//����, ���� ������
	class Vector4d {

	protected:
		static const int ROW = 4; //���� �� = 4�� ����
		std::vector<std::vector<double>> _col; //���� 3���� �������� ����(4*n ���) 
		int _col_size; //�� ����
		Vector4d(int col_size) : _col_size(col_size), _col(col_size, std::vector<double>(ROW)) {} //�� ����� col_size�� ����� ����

	public:
		const static Vector4d zero_vector;
		const static Vector4d zero_point;

		Vector4d(bool is_vector = true); //������ �Ǵ� ���� ����
		Vector4d(std::initializer_list<double> list); //initializer_list�� ���, 3���� homogenous ����(��) �ʱ�ȭ
		Vector4d(const Vector4d& rhs); 		//���� ������
		Vector4d(Vector4d&& rhs) noexcept;	//�̵� ������
		Vector4d(const Matrix4d& rhs);

		double& operator[](int idx);					//���� ���� ����		
		std::vector<double>& col(int idx = 0) const;	//������ ���� ����
		bool operator==(const Vector4d& rhs) const;		//���� ����
		bool operator!=(const Vector4d& rhs) const;		//�񵿵� ����
		Vector4d operator*(double k) const;				//����� ����
		Vector4d operator/(double k) const;				//����� ����
		Vector4d operator-() const;						//��ȣ ����
		Vector4d operator+(const Vector4d& rhs) const;	//���� ����
		Vector4d operator-(const Vector4d& rhs) const;	//���� ����
		Vector4d operator*(const Vector4d& rhs) const;	//���� ����
		double dot(const Vector4d& rhs) const;			//���� ����
		Vector4d point() const;		//��ü�� ���̶�� ����
		Vector4d vector() const;	//��ü�� ���Ͷ�� ����

		Vector4d& operator=(const Vector4d& rhs);		//���� ������
		Vector4d& operator=(Vector4d&& rhs) noexcept;	//�̵� ���Կ�����
		friend std::ostream& operator<<(std::ostream& os, const Vector4d& m); //cout���� ������ ���(���� ��� ����ȭ�� 3���� ��ǥ, ������ ��� 3���� ������ ���)
		std::string full_format() const; //���� ��ü ������ ��� ǥ��

		int col_size() const { return _col_size; } // �� ���� ���
		bool is_point() const; //��ü�� ������ Ȯ��
		bool is_vector() const; //��ü�� �������� Ȯ��
		double norm() const; //������ ũ��(norm) ���
		double cos(const Vector4d rhs) const; //�־��� ���Ϳ��� ������ cos�� ���
		Vector4d normalize() const; //����ȭ ����(���� ��� 4��° ���� 1�� ����, ������ ��� ũ�⸦ 1�� ����)
		Matrix4d append(const Vector4d& rhs) const;	//�� ��� �����̱�
	};

	Vector4d operator*(double k, const Vector4d& m); //(��ȯ��Ģ)��� ��Į��� ����
}


//����� ����
namespace jangan_lee_my_matrix {

	//���� 4���� 4*n 3���� homogeneous ����� ǥ���ϴ� Ŭ����
	class Matrix4d : public Vector4d {
	public:
		Matrix4d(int col_size = ROW) : Vector4d(col_size) {} //�� ����� col_size�� ����� ����
		Matrix4d(const Matrix4d& rhs) : Vector4d(rhs) {}				//���� ������
		Matrix4d(Matrix4d&& rhs) noexcept : Vector4d(std::move(rhs)) {}	//�̵� ������
		Matrix4d(const Vector4d& v1, const Vector4d& v2, const Vector4d& v3, const Vector4d& v4); //���� 4���� 4*4 ��� ����
		Matrix4d(std::initializer_list<std::vector<double>> list); //initializer_list�� ���, ��ü������ n*4 ��� �ʱ�ȭ
		Matrix4d(const Vector4d& rhs); //Vector4d�� ��ķ� ��ȯ

		std::vector<double>& operator[](int idx); //������ ���� ����	
		bool operator==(const Matrix4d& rhs) const;		//���� ����
		bool operator!=(const Matrix4d& rhs) const;		//�񵿵� ����	
		Matrix4d operator*(double k) const;				//��Į��� ����
		Matrix4d operator/(double k) const;				//��Į��� ����
		Matrix4d operator-() const;						//��ȣ ����
		Matrix4d operator+(const Matrix4d& rhs) const;	//����� ���� ����(���� ��ġ�ϴ� ��쿡�� ����)
		Matrix4d operator-(const Matrix4d& rhs) const;	//����� ���� ����(���� ��ġ�ϴ� ��쿡�� ����)
		Matrix4d operator*(const Matrix4d& rhs) const;  //��İ� ����

		Matrix4d& operator=(const Matrix4d& rhs);		//���Կ�����
		Matrix4d& operator=(Matrix4d&& rhs) noexcept;	//�̵� ���Կ�����
		friend std::ostream& operator<<(std::ostream& os, const Matrix4d& m); //cout ���

		int col_size() const { return _col_size; }	//�� ���� ��ȯ
		int row_size() const { return ROW; }		//�� ���� ��ȯ
	};

	Matrix4d operator*(double k, const Matrix4d& m); //(��ȯ��Ģ)��� ��Į��� ����

}
#endif