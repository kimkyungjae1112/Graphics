//201986 소프트웨어공학과 이장안
//3차원 동차 좌표계상의 행렬 및 벡터 클래스를 구현한다.
#include "MyMatrix.h"
#include "CgMath.h"
#include <exception>
#include <vector>
#include <initializer_list>
#include <iomanip>


//Vector4d 관련 기능 구현
namespace jangan_lee_my_matrix {

	/****************  static 변수  ****************/

	const Vector4d Vector4d::zero_vector = Vector4d(true);
	const Vector4d Vector4d::zero_point = Vector4d(false);

	/****************  생성자  ****************/

	/* 영벡터 또는 원점 생성 */
	Vector4d::Vector4d(bool is_vector) : Vector4d(1) {
		_col[0][ROW - 1] = (int)(!is_vector);
	}

	/* initializer_list를 사용, 3차원 homogenous 벡터(점) 초기화 */
	Vector4d::Vector4d(std::initializer_list<double> list) : Vector4d(1) {
		auto it = list.begin();
		for (int i = 0; i < ROW && it != list.end(); i++) {
			_col[0][i] = *it;
			it++;
		}
	}

	/* 복사 생성자 */
	Vector4d::Vector4d(const Vector4d& rhs) {
		this->_col_size = rhs._col_size;
		this->_col = rhs._col;
	}

	/* 이동 생성자 */
	Vector4d::Vector4d(Vector4d&& rhs) noexcept : 
		_col_size(std::move(rhs._col_size)), 
		_col(std::move(rhs._col)) { }

	Vector4d::Vector4d(const Matrix4d& rhs) : Vector4d(1)
	{
		for (int r = 0; r < ROW; r++)
			_col[0][r] = rhs.col(0)[r];
	}




	/****************  연산자 오버로딩  ****************/

	/* 원소 참조 연산 */
	double& Vector4d::operator[](int idx) {
		return _col[0][idx];
	}

	std::vector<double>& Vector4d::col(int idx) const
	{
		return const_cast<std::vector<double> &>(_col[idx]);
	}

	/* 상수배 연산 */
	Vector4d Vector4d::operator*(double k) const {
		Vector4d ret = *this;

		for (int c = 0; c < _col_size; c++)
			for (int r = 0; r < ROW; r++)
				ret._col[c][r] *= k;

		return ret;
	}

	/* 상수배 연산 */
	Vector4d Vector4d::operator/(double k) const
	{
		return *this * (1.0 / k);
	}

	/* 동등 연산 */
	bool Vector4d::operator==(const Vector4d& rhs) const
	{
		return _col_size == rhs._col_size && _col == rhs._col;
	}

	/* 비동등 연산 */
	bool Vector4d::operator!=(const Vector4d& rhs) const
	{
		return !(*this == rhs);
	}

	/* 부호 연산 */
	Vector4d Vector4d::operator-() const {
		return *this * -1;
	}

	/* 덧셈 연산 */
	Vector4d Vector4d::operator+(const Vector4d& rhs) const {
		//차원이 동일하지 않으면 덧셈 불가
		if (_col_size != rhs._col_size) {
			std::string msg = "Matrix4d Operation Error(add): operand간 차원이 불일치함";
			std::cout << msg << std::endl;
			throw std::logic_error(msg);
		}

		Vector4d ret = *this;
		for (int c = 0; c < _col_size; c++)
			for (int r = 0; r < ROW; r++)
				ret._col[c][r] += rhs._col[c][r];

		return ret;
	}

	/* 뺄셈 연산 */
	Vector4d Vector4d::operator-(const Vector4d& rhs) const {
		//차원이 동일하지 않으면 행렬 뺄셈 불가
		if (_col_size != rhs._col_size) {
			std::string msg = "Matrix4d Operation Error(subtract): operand간 차원이 불일치함";
			std::cout << msg << std::endl;
			throw std::logic_error(msg);
		}

		return *this + -rhs;
	}

	/* 외적 연산 */
	Vector4d Vector4d::operator*(const Vector4d& rhs) const
	{
		//피연산자가 벡터가 아니면 연산 불가능
		if (is_point() || rhs.is_point()) {
			std::string msg = "Vector4d Operation Error(cross): operand는 모두 벡터여야 함";
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

	/* 내적 연산 */
	double Vector4d::dot(const Vector4d& rhs) const
	{
		double ret = 0;
		for (int i = 0; i < ROW; i++)
			ret += _col[0][i] * rhs._col[0][i];

		return ret;
	}

	/* 객체를 점이라고 간주 */
	Vector4d Vector4d::point() const
	{
		auto& a = _col[0];
		return Vector4d({ a[0], a[1], a[2], 1 });
	}

	/* 객체를 벡터라고 간주 */
	Vector4d Vector4d::vector() const
	{
		auto& a = _col[0];
		return Vector4d({ a[0], a[1], a[2], 0 });
	}

	/* 대입 연산자 */
	Vector4d& Vector4d::operator=(const Vector4d& rhs) {
		this->_col_size = rhs._col_size;
		this->_col = rhs._col;
		return *this;
	}

	/* 이동 대입연산자 */
	Vector4d& Vector4d::operator=(Vector4d&& rhs) noexcept {
		this->_col_size = std::move(rhs._col_size);
		this->_col = std::move(rhs._col);
		return *this;
	}

	/* 객체를 cout(os)을 이용하여 간단히 출력(점인 경우 정규화된 3차원 좌표, 벡터인 경우 3차원 정보만 출력) */
	std::ostream& operator<<(std::ostream& os, const Vector4d& m)
	{
		Vector4d v = m.is_vector() ? m : m.normalize();
		char buf[256] = { 0 };
		std::snprintf(buf, 256, "(%lf, %lf, %lf)", v[0], v[1], v[2]);
		return os << buf;
	}

	/* 현재 객체 정보를 모두 표현 */
	std::string Vector4d::full_format() const {
		char buf[256] = { 0 };
		std::snprintf(buf, 256, "[%lf, %lf, %lf, %lf]", _col[0][0], _col[0][1], _col[0][2], _col[0][3]);
		return std::string(buf);
	}




	/****************  멤버 함수  ****************/

	/* 객체가 점인지 확인 */
	bool Vector4d::is_point() const
	{
		return !CgMath::is_zero(_col[0][ROW - 1]);
	}

	/* 객체가 벡터인지 확인 */
	bool Vector4d::is_vector() const {
		return !is_point();
	}

	/* 벡터의 크기(norm) 계산 */
	double Vector4d::norm() const
	{
		return std::sqrt(dot(*this));
	}

	/* 정규화 수행(점인 경우 4번째 값을 1로 만듦, 벡터인 경우 크기를 1로 만듦) */
	Vector4d Vector4d::normalize() const {
		if (is_vector()) {
			return *this / norm();
		}
		else {
			return *this / _col[0][ROW - 1];
		}
	}

	/* 주어진 벡터와의 각도의 cos값 계산 */
	double Vector4d::cos(const Vector4d rhs) const
	{
		return dot(rhs) / (norm() * rhs.norm());
	}

	/* 두 벡터 덧붙이기 */
	Matrix4d Vector4d::append(const Vector4d& rhs) const {
		//두 벡터를 가로로 더해 열의 수가 늘어난다.
		Vector4d ret = *this;
		ret._col_size += rhs._col_size;

		for (int i = 0; i < rhs._col_size; i++)
			ret._col.push_back(rhs._col[i]);

		return ret;
	}



	/****************  비 멤버함수 연산자 오버로딩 ****************/

	/* (교환법칙)행렬 스칼라배 연산 */
	Vector4d operator*(double k, const Vector4d& m) {
		return m * k;
	}
}




//Matrix4d 관련 기능 구현
namespace jangan_lee_my_matrix {

	/****************  생성자  ****************/

	/* initializer_list 사용, 구체값으로 n * 4 행렬 초기화 */
	Matrix4d::Matrix4d(std::initializer_list<std::vector<double>> list) : Matrix4d(0) {
		//입력된 행 중 길이가 최대인 행(=열의 개수)구하기
		for (auto it = list.begin(); it != list.end(); it++)
			_col_size = std::max(_col_size, (int)it->size());

		//initializer_list로 행렬을 초기화하기
		_col.resize(_col_size, std::vector<double>(4));
		int r = 0;
		for (auto it = list.begin(); it != list.end(); it++, r++) {
			for (size_t c = 0; c < (size_t)_col_size; c++)
				_col[c][r] = c < it->size() ? (*it)[c] : 0;
		}
	}



	/****************  연산자 오버로딩  ****************/

	Matrix4d::Matrix4d(const Vector4d& rhs) : Vector4d(rhs.col_size())
	{
		for (int c = 0; c < _col_size; c++)
			for (int r = 0; r < ROW; r++)
				_col[c][r] = rhs.col(c)[r];
	}

	/* idx번째 열벡터 참조 연산 */
	std::vector<double>& Matrix4d::operator[](int idx) {
		return _col[idx];
	}

	/* 벡터 4개로 4*4 행렬 생성 */
	Matrix4d::Matrix4d(const Vector4d& v1, const Vector4d& v2, const Vector4d& v3, const Vector4d& v4) : Matrix4d(4) {
		_col[0] = v1.col(0);
		_col[1] = v2.col(0);
		_col[2] = v3.col(0);
		_col[3] = v4.col(0);
	}

	/* 동등 연산 */
	bool Matrix4d::operator==(const Matrix4d& rhs) const
	{
		return Vector4d::operator==(rhs);
	}

	/* 비동등 연산 */
	bool Matrix4d::operator!=(const Matrix4d& rhs) const
	{
		return Vector4d::operator!=(rhs);
	}

	/* 스칼라배 연산 */
	Matrix4d Matrix4d::operator*(double k) const
	{
		return Vector4d::operator*(k);
	}

	/* 스칼라배 연산 */
	Matrix4d Matrix4d::operator/(double k) const
	{
		return Vector4d::operator/(k);
	}

	/* 부호 연산 */
	Matrix4d Matrix4d::operator-() const
	{
		return Vector4d::operator-();
	}

	/* 뺄셈 연산 */
	Matrix4d Matrix4d::operator-(const Matrix4d& rhs) const
	{
		return Vector4d::operator-(rhs);
	}

	/* 덧셈 연산 */
	Matrix4d Matrix4d::operator+(const Matrix4d& rhs) const
	{
		return  Vector4d::operator+(rhs);
	}

	/* 행렬의 곱셈(차원이 행렬곱 가능한 경우에만 수행) */
	Matrix4d Matrix4d::operator*(const Matrix4d& rhs) const {
		//차원이 행렬곱 가능하지 않으면 행렬 곱셈 불가
		if (_col_size != ROW) {
			std::string msg = "Matrix4d Operation Error(multiply): operand간 차원이 행렬곱 하기에 적절하지 않음";
			std::cout << msg << std::endl;
			throw std::logic_error(msg);
		}

		//행렬곱 수행
		Matrix4d ret(rhs._col_size);
		for (int c = 0; c < rhs._col_size; c++)
			for (int r = 0; r < ROW; r++)
				for (int k = 0; k < ROW; k++)
					ret[c][r] += rhs._col[c][k] * this->_col[k][r];
		
		return ret;
	}

	/* 대입연산자 */
	Matrix4d& Matrix4d::operator=(const Matrix4d& rhs) {
		Vector4d::operator=(rhs);
		return *this;
	}
	
	/* 이동 대입연산자 */
	Matrix4d& Matrix4d::operator=(Matrix4d&& rhs) noexcept {
		Vector4d::operator=(std::move(rhs));
		return *this;
	}

	/* 객체를 cout을 이용하여 출력 */
	std::ostream& operator<<(std::ostream& os, const Matrix4d& m) {
		std::ios_base::fmtflags prev_setting(os.flags()); //ostream 세팅 백업

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

		os.flags(prev_setting); //ostream 세팅 복원
		return os;
	}



	/****************  비 멤버함수 연산자 오버로딩 ****************/

	/* (교환법칙)행렬 스칼라배 연산 */
	Matrix4d operator*(double k, const Matrix4d& m) {
		return m * k;
	}

}

