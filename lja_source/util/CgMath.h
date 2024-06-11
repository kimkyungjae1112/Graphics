#pragma once
#ifndef __CG_MATH_H__
#define __CG_MATH_H__

#include <cmath>
#include <optional>
#include "CgObject.h"
#include "Interval.h"

class CgMath {
public:
	//파이값 리턴
	const inline static double PI() { return atan(1) * 4; }
	const inline static double DegToRad(double degree) { return degree * PI() / 180.0; }
	const inline static double LinearInterpolation(const double& cur_min, const double& cur_max, const double& to_convert, const double& new_min, const double& new_max) {
		double&& ret = (new_min * cur_max - cur_min * new_max + (new_max - new_min) * to_convert) / (cur_max - cur_min);
		return ret < new_min ? new_min : (ret > new_max ? new_max : ret);
	}
	const inline static Color LinearInterpolation(const Color& cur_min, const Color& cur_max, const Color& to_convert, const Color& new_min, const Color& new_max) {
		double&& r = CgMath::LinearInterpolation(cur_min.r, cur_max.r, to_convert.r, new_min.r, new_max.r);
		double&& g = CgMath::LinearInterpolation(cur_min.g, cur_max.g, to_convert.g, new_min.g, new_max.g);
		double&& b = CgMath::LinearInterpolation(cur_min.b, cur_max.b, to_convert.b, new_min.b, new_max.b);
		return Color(std::move(r), std::move(g), std::move(b));
	}
	const inline static bool is_zero(const double& d) { return std::fabs(d) < machine_epsilon(); }
	constexpr inline static double machine_epsilon() { return std::numeric_limits<double>::epsilon(); }

	template <class Func> inline static std::optional<double> IM(const Func& f, const Interval& i) {
		constexpr double eps = machine_epsilon();
		constexpr double d_eps = machine_epsilon() * 1e1; //10배 널널한 엡실론
		//double y_left = f(i.a); //구간 왼쪽의 함숫값
		//double y_right = f(i.b); //구간 오른쪽의 함숫값

		if (i.Range() < d_eps /*|| abs(y_left) < d_eps || abs(y_right) < d_eps*/) {
			//if ((y_left < 0) != (y_right < 0)) { //중근 여부 판별식

				return i.Center(); //중근이 아닌 근만 근으로 한다.
			//}
			//else {
			//	return std::nullopt; //중근
			//}
		}

		Interval&& j = f(i);
		if (!j.Contains(0)) return std::nullopt;

		Interval i1(i.a, i.Center());
		Interval i2(i.Center() + eps, i.b);
		std::optional<double>&& t = IM(f, i1);

		return t.has_value() ? std::move(t) : IM(f, i2);
	}

};

# endif