#include "interval.h"
#include <limits>
#include <cmath>
#include <iostream>

Interval Interval::operator*(const Interval& interval) const
{
    double a = Smaller * interval.Smaller;
    double b = Smaller * interval.Bigger;
    double c = Bigger * interval.Smaller;
    double d = Bigger * interval.Bigger;

    return Interval(std::min({a, b, c, d}), std::max({a, b, c, d})) ;
}

Interval Interval::operator/(const Interval& interval) const
{
    double a = Smaller / interval.Smaller;
    double b = Smaller / interval.Bigger;
    double c = Bigger / interval.Smaller;
    double d = Bigger / interval.Bigger;

    return Interval(std::min({a, b, c, d}), std::max({a, b, c, d}));
}

Interval Interval::operator+(const Interval& interval) const
{
    return { Smaller + interval.Smaller, Bigger + interval.Bigger };
}

Interval Interval::operator-(const Interval& interval) const
{
    return { Smaller - interval.Bigger, Bigger - interval.Smaller };
}

Interval exp(const Interval& interval)
{
    return Interval(std::exp(interval.Smaller), std::exp(interval.Bigger));
}

Interval Interval::operator-() const
{
    return Interval(-Bigger, -Smaller);
}

Interval Interval::operator+(const double& i) const
{
    return Interval(Smaller + i, Bigger + i);
}

Interval Interval::operator-(const double& i) const 
{
    return Interval(Smaller - i, Bigger - i);
}

Interval Interval::operator*(const double& i) const
{
    return (i > 0) ? Interval(Smaller * i, Bigger * i) : Interval(Bigger * i, Smaller * i);
}

Interval operator+(const double& i, const Interval& interval)
{
    return interval + i;
}

Interval operator-(const double& i, const Interval& interval)
{
    return interval - i;
}

Interval operator*(const double& i, const Interval& interval)
{
    return interval * i;
}



std::optional<double> IntervalMethod(const std::function<Interval(Interval)>& func, const Interval& i)
{
    constexpr static double m_eps = std::numeric_limits<double>::epsilon();
    constexpr static double d_eps = m_eps * 1e1; //10¹è ´õ ³ÐÀº machine_epsilon

    if (i.Range() < 0.022)
    {
        return i.Center();
    }

    Interval J = func(i);
    if (!J.Contain(0)) return std::nullopt;

    Interval interval1 = { i.Smaller, i.Center() };
    Interval interval2 = { i.Center() + m_eps, i.Bigger };

    std::optional<double> Root = IntervalMethod(func, interval1);

    return Root.has_value() ? Root : IntervalMethod(func, interval2);
}

std::ostream& operator<<(std::ostream& os, const Interval& interval)
{
    return os << "{ " << interval.Smaller << ", " << interval.Bigger << " }";
}