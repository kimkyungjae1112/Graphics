//201986 ����Ʈ������а� �����
//3���� ���� ��ǥ����� ��� �� ���� Ŭ������ �����Ѵ�.
#include "MyMatrix.h"
#include "CgMath.h"
#include <exception>
#include <vector>
#include <initializer_list>
#include <iomanip>


//Vector4d ���� ��� ����
namespace jangan_lee_my_matrix {

	/****************  static ����  ****************/

	const Vector4d Vector4d::zero_vector = Vector4d(true);
	const Vector4d Vector4d::zero_point = Vector4d(false);

	/****************  ������  ****************/

	/* ������ �Ǵ� ���� ���� */
	Vector4d::Vector4d(bool is_vector) : Vector4d(1) {
		_col[0][ROW - 1] = (int)(!is_vector);
	}

	/* initializer_list�� ���, 3���� homogenous ����(��) �ʱ�ȭ */
	Vector4d::Vector4d(std::initializer_list<double> list) : Vector4d(1) {
		auto it = list.begin();
		for (int i = 0; i < ROW && it != list.end(); i++) {
			_col[0][i] = *it;
			it++;
		}
	}

	/* ���� ������ */
	Vector4d::Vector4d(const Vector4d& rhs) {
		this->_col_size = rhs._col_size;
		this->_col = rhs._col;
	}

	/* �̵� ������ */
	Vector4d::Vector4d(Vector4d&& rhs) noexcept : 
		_col_size(std::move(rhs._col_size)), 
		_col(std::move(rhs._col)) { }

	Vector4d::Vector4d(const Matrix4d& rhs) : Vector4d(1)
	{
		for (int r = 0; r < ROW; r++)
			_col[0][r] = rhs.col(0)[r];
	}




	/****************  ������ �����ε�  ****************/

	/* ���� ���� ���� */
	double& Vector4d::operator[](int idx) {
		return _col[0][idx];
	}

	std::vector<double>& Vector4d::col(int idx) const
	{
		return const_cast<std::vector<double> &>(_col[idx]);
	}

	/* ����� ���� */
	Vector4d Vector4d::operator*(double k) const {
		Vector4d ret = *this;

		for (int c = 0; c < _col_size; c++)
			for (int r = 0; r < ROW; r++)
				ret._col[c][r] *= k;

		return ret;
	}

	/* ����� ���� */
	Vector4d Vector4d::operator/(double k) const
	{
		return *this * (1.0 / k);
	}

	/* ���� ���� */
	bool Vector4d::operator==(const Vector4d& rhs) const
	{
		return _col_size == rhs._col_size && _col == rhs._col;
	}

	/* �񵿵� ���� */
	bool Vector4d::operator!=(const Vector4d& rhs) const
	{
		return !(*this == rhs);
	}

	/* ��ȣ ���� */
	Vector4d Vector4d::operator-() const {
		return *this * -1;
	}

	/* ���� ���� */
	Vector4d Vector4d::operator+(const Vector4d& rhs) const {
		//������ �������� ������ ���� �Ұ�
		if (_col_size != rhs._col_size) {
			std::string msg = "Matrix4d Operation Error(add): operand�� ������ ����ġ��";
			std::cout << msg << std::endl;
			throw std::logic_error(msg);
		}

		Vector4d ret = *this;
		for (int c = 0; c < _col_size; c++)
			for (int r = 0; r < ROW; r++)
				ret._col[c][r] += rhs._col[c][r];

		return ret;
	}

	/* ���� ���� */
	Vector4d Vector4d::operator-(const Vector4d& rhs) const {
		//������ �������� ������ ��� ���� �Ұ�
		if (_col_size != rhs._col_size) {
			std::string msg = "Matrix4d Operation Error(subtract): operand�� ������ ����ġ��";
			std::cout << msg << std::endl;
			throw std::logic_error(msg);
		}

		return *this + -rhs;
	}

	/* ���� ���� */
	Vector4d Vector4d::operator*(const Vector4d& rhs) const
	{
		//�ǿ����ڰ� ���Ͱ� �ƴϸ� ���� �Ұ���
		if (is_point() || rhs.is_point()) {
			std::string msg = "Vector4d Operation Error(cross): operand�� ��� ���Ϳ��� ��";
			std::cout << msg << std::endl;
			throw std::logic_error(msg);
		}

		auto& a = _col[0];
		auto& b = rhs._col[0];

		return {
			a[1] * b[2] - a[2] * b[1],
			a[2] * b[0] - a[0] * b[2],
			a[0] * b[1] - a[1] * b[0],
			0 };
	}

	/* ���� ���� */
	double Vector4d::dot(const Vector4d& rhs) const
	{
		double ret = 0;
		for (int i = 0; i < ROW; i++)
			ret += _col[0][i] * rhs._col[0][i];

		return ret;
	}

	/* ��ü�� ���̶�� ���� */
	Vector4d Vector4d::point() const
	{
		auto& a = _col[0];
		return Vector4d({ a[0], a[1], a[2], 1 });
	}

	/* ��ü�� ���Ͷ�� ���� */
	Vector4d Vector4d::vector() const
	{
		auto& a = _col[0];
		return Vector4d({ a[0], a[1], a[2], 0 });
	}

	/* ���� ������ */
	Vector4d& Vector4d::operator=(const Vector4d& rhs) {
		this->_col_size = rhs._col_size;
		this->_col = rhs._col;
		return *this;
	}

	/* �̵� ���Կ����� */
	Vector4d& Vector4d::operator=(Vector4d&& rhs) noexcept {
		this->_col_size = std::move(rhs._col_size);
		this->_col = std::move(rhs._col);
		return *this;
	}

	/* ��ü�� cout(os)�� �̿��Ͽ� ������ ���(���� ��� ����ȭ�� 3���� ��ǥ, ������ ��� 3���� ������ ���) */
	std::ostream& operator<<(std::ostream& os, const Vector4d& m)
	{
		Vector4d v = m.is_vector() ? m : m.normalize();
		char buf[256] = { 0 };
		std::snprintf(buf, 256, "(%lf, %lf, %lf)", v[0], v[1], v[2]);
		return os << buf;
	}

	/* ���� ��ü ������ ��� ǥ�� */
	std::string Vector4d::full_format() const {
		char buf[256] = { 0 };
		std::snprintf(buf, 256, "[%lf, %lf, %lf, %lf]", _col[0][0], _col[0][1], _col[0][2], _col[0][3]);
		return std::string(buf);
	}




	/****************  ��� �Լ�  ****************/

	/* ��ü�� ������ Ȯ�� */
	bool Vector4d::is_point() const
	{
		return !CgMath::is_zero(_col[0][ROW - 1]);
	}

	/* ��ü�� �������� Ȯ�� */
	bool Vector4d::is_vector() const {
		return !is_point();
	}

	/* ������ ũ��(norm) ��� */
	double Vector4d::norm() const
	{
		return std::sqrt(dot(*this));
	}

	/* ����ȭ ����(���� ��� 4��° ���� 1�� ����, ������ ��� ũ�⸦ 1�� ����) */
	Vector4d Vector4d::normalize() const {
		if (is_vector()) {
			return *this / norm();
		}
		else {
			return *this / _col[0][ROW - 1];
		}
	}

	/* �־��� ���Ϳ��� ������ cos�� ��� */
	double Vector4d::cos(const Vector4d rhs) const
	{
		return dot(rhs) / (norm() * rhs.norm());
	}

	/* �� ���� �����̱� */
	Matrix4d Vector4d::append(const Vector4d& rhs) const {
		//�� ���͸� ���η� ���� ���� ���� �þ��.
		Vector4d ret = *this;
		ret._col_size += rhs._col_size;

		for (int i = 0; i < rhs._col_size; i++)
			ret._col.push_back(rhs._col[i]);

		return ret;
	}



	/****************  �� ����Լ� ������ �����ε� ****************/

	/* (��ȯ��Ģ)��� ��Į��� ���� */
	Vector4d operator*(double k, const Vector4d& m) {
		return m * k;
	}
}




//Matrix4d ���� ��� ����
namespace jangan_lee_my_matrix {

	/****************  ������  ****************/

	/* initializer_list ���, ��ü������ n * 4 ��� �ʱ�ȭ */
	Matrix4d::Matrix4d(std::initializer_list<std::vector<double>> list) : Matrix4d(0) {
		//�Էµ� �� �� ���̰� �ִ��� ��(=���� ����)���ϱ�
		for (auto it = list.begin(); it != list.end(); it++)
			_col_size = std::max(_col_size, (int)it->size());

		//initializer_list�� ����� �ʱ�ȭ�ϱ�
		_col.resize(_col_size, std::vector<double>(4));
		int r = 0;
		for (auto it = list.begin(); it != list.end(); it++, r++) {
			for (size_t c = 0; c < (size_t)_col_size; c++)
				_col[c][r] = c < it->size() ? (*it)[c] : 0;
		}
	}



	/****************  ������ �����ε�  ****************/

	Matrix4d::Matrix4d(const Vector4d& rhs) : Vector4d(rhs.col_size())
	{
		for (int c = 0; c < _col_size; c++)
			for (int r = 0; r < ROW; r++)
				_col[c][r] = rhs.col(c)[r];
	}

	/* idx��° ������ ���� ���� */
	std::vector<double>& Matrix4d::operator[](int idx) {
		return _col[idx];
	}

	/* ���� 4���� 4*4 ��� ���� */
	Matrix4d::Matrix4d(const Vector4d& v1, const Vector4d& v2, const Vector4d& v3, const Vector4d& v4) : Matrix4d(4) {
		_col[0] = v1.col(0);
		_col[1] = v2.col(0);
		_col[2] = v3.col(0);
		_col[3] = v4.col(0);
	}

	/* ���� ���� */
	bool Matrix4d::operator==(const Matrix4d& rhs) const
	{
		return Vector4d::operator==(rhs);
	}

	/* �񵿵� ���� */
	bool Matrix4d::operator!=(const Matrix4d& rhs) const
	{
		return Vector4d::operator!=(rhs);
	}

	/* ��Į��� ���� */
	Matrix4d Matrix4d::operator*(double k) const
	{
		return Vector4d::operator*(k);
	}

	/* ��Į��� ���� */
	Matrix4d Matrix4d::operator/(double k) const
	{
		return Vector4d::operator/(k);
	}

	/* ��ȣ ���� */
	Matrix4d Matrix4d::operator-() const
	{
		return Vector4d::operator-();
	}

	/* ���� ���� */
	Matrix4d Matrix4d::operator-(const Matrix4d& rhs) const
	{
		return Vector4d::operator-(rhs);
	}

	/* ���� ���� */
	Matrix4d Matrix4d::operator+(const Matrix4d& rhs) const
	{
		return  Vector4d::operator+(rhs);
	}

	/* ����� ����(������ ��İ� ������ ��쿡�� ����) */
	Matrix4d Matrix4d::operator*(const Matrix4d& rhs) const {
		//������ ��İ� �������� ������ ��� ���� �Ұ�
		if (_col_size != ROW) {
			std::string msg = "Matrix4d Operation Error(multiply): operand�� ������ ��İ� �ϱ⿡ �������� ����";
			std::cout << msg << std::endl;
			throw std::logic_error(msg);
		}

		//��İ� ����
		Matrix4d ret(rhs._col_size);
		for (int c = 0; c < rhs._col_size; c++)
			for (int r = 0; r < ROW; r++)
				for (int k = 0; k < ROW; k++)
					ret[c][r] += rhs._col[c][k] * this->_col[k][r];
		
		return ret;
	}

	/* ���Կ����� */
	Matrix4d& Matrix4d::operator=(const Matrix4d& rhs) {
		Vector4d::operator=(rhs);
		return *this;
	}
	
	/* �̵� ���Կ����� */
	Matrix4d& Matrix4d::operator=(Matrix4d&& rhs) noexcept {
		Vector4d::operator=(std::move(rhs));
		return *this;
	}

	/* ��ü�� cout�� �̿��Ͽ� ��� */
	std::ostream& operator<<(std::ostream& os, const Matrix4d& m) {
		std::ios_base::fmtflags prev_setting(os.flags()); //ostream ���� ���

		os.precision(6);
		os << std::fixed;
		os << "[";
		for (int r = 0; r < Matrix4d::ROW; r++) {
			os << (r != 0 ? " " : "") << "[ ";
			for (int c = 0; c < m._col_size; c++) {
				os << std::setw(9) << m._col[c][r] << ((c == m._col_size - 1) ? " " : ", ");
			}
			os << "]" << ((r == Matrix4d::ROW - 1) ? "" : "\n");
		}
		os << "]" << std::endl;

		os.flags(prev_setting); //ostream ���� ����
		return os;
	}



	/****************  �� ����Լ� ������ �����ε� ****************/

	/* (��ȯ��Ģ)��� ��Į��� ���� */
	Matrix4d operator*(double k, const Matrix4d& m) {
		return m * k;
	}

}

