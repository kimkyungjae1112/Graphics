#pragma once
#ifndef __INTERVAL_H__
#define __INTERVAL_H__

#include <memory>
#include <ostream>

class Interval {
public:
	double a;
	double b;

	template <typename t1, typename t2> Interval(t1&& a, t2&& b) : a(std::forward<t1>(a)), b(std::forward<t2>(b)) {
		if (this->a > this->b) std::swap(this->a, this->b);
	}
	Interval() : Interval(0, 0) {}
	Interval(const Interval& rhs) : a(rhs.a), b(rhs.b) {}
	Interval(Interval&& rhs) noexcept : a(std::move(rhs.a)), b(std::move(rhs.b)) {}
	inline Interval& operator=(const Interval& rhs) {
		this->a = rhs.a;
		this->b = rhs.b;
		return *this;
	}
	inline Interval& operator=(Interval&& rhs) noexcept {
		this->a = std::move(rhs.a);
		this->b = std::move(rhs.b);
		return *this;
	}

	inline Interval operator+(const Interval& rhs) const {
		return Interval(a + rhs.a, b + rhs.b);
	}
	inline Interval operator+(const double& rhs) const {
		return Interval(a + rhs, b + rhs);
	}
	inline Interval operator-() const {
		return Interval(-a, -b);
	}
	inline Interval operator-(const Interval& rhs) const {
		return Interval(a - rhs.b, b - rhs.a);
	}
	inline Interval operator-(const double& rhs) const {
		return Interval(a - rhs, b - rhs);
	}
	inline Interval operator*(const Interval& rhs) const {
		return Interval(
			std::min({ a * rhs.a, a * rhs.b, b * rhs.a, b * rhs.b }), 
			std::max({ a * rhs.a, a * rhs.b, b * rhs.a, b * rhs.b }));
	}
	inline Interval operator*(const double& rhs) const {
		return Interval(a * rhs, b * rhs);
	}
	inline Interval operator/(const Interval& rhs) const {
		return Interval(
			std::min({ a / rhs.a, a / rhs.b, b / rhs.a, b / rhs.b }), 
			std::max({ a / rhs.a, a / rhs.b, b / rhs.a, b / rhs.b }));
	}

	inline bool Contains(const double& x) const {
		return a <= x && x <= b;
	}
	inline double Range() const {
		return b - a;
	}
	inline double Center() const {
		return (a + b) / 2;
	}

	inline friend Interval operator+(const double& lhs, const Interval& rhs) {
		return rhs + lhs;
	}
	inline friend Interval operator-(const double& lhs, const Interval& rhs) {
		return rhs - lhs;
	}
	inline friend Interval operator*(const double& lhs, const Interval& rhs) {
		return rhs * lhs;
	}
	inline friend Interval operator/(const double& lhs, const Interval& rhs) {
		return Interval(lhs / rhs.b, lhs / rhs.a);
	}
	inline friend std::ostream& operator<<(std::ostream& os, const Interval& i) {
		os << "Interval[" << i.a << ", " << i.b << "]";
		return os;
	}
};

inline Interval pow(const Interval& _Ival, const int& _Exp) {
	if (_Exp <= 0) {
		std::cout << "Interval2d의 지수는 0이나 음수가 될 수 없음";
		exit(EXIT_FAILURE);
	}

	const double& a = _Ival.a;
	const double& b = _Ival.b;
	double&& a_pow = pow(a, _Exp);
	double&& b_pow = pow(b, _Exp);

	if (_Exp % 2 == 0) {
		return Interval(
			_Ival.Contains(0) ? 0.0 : std::min(std::move(a_pow), std::move(b_pow)),
			std::max(std::move(a_pow), std::move(b_pow)));
	}
	else {
		return Interval(std::move(a_pow), std::move(b_pow));
	}
}
inline Interval exp(const Interval& _Ival) {
	return Interval(std::exp(_Ival.a), std::exp(_Ival.b));
}


#endif