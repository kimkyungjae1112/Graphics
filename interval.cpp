#include "interval.h"
#include <limits>
#include <cmath>

double Interval::IntervalMethod(std::vector<double> (*ptr)(double))
{
    if (abs(Bigger - Smaller) < 1e-6) return (Bigger + Smaller) / 2.0;

    Interval J = FindJ(ptr);
    if (J.Smaller * J.Bigger > 0) return std::numeric_limits<double>::quiet_NaN();

    double Center = (Bigger + Smaller) / 2.0;
    Interval interval1 = { Smaller, Center };
    Interval interval2 = { Center, Bigger };

    double Root = interval1.IntervalMethod(ptr);

    return !std::isnan(Root) ? Root : interval2.IntervalMethod(ptr);
}

std::vector<double> Interval::FindAllRoot(std::vector<double>(*F)(double))
{
    std::vector<double> Roots;
    double Start = 0.0;

    double Root = IntervalMethod(F);
    if (!std::isnan(Root)) Roots.push_back(Root);

    while (!std::isnan(Root))
    {
        Start = Root;
        Interval interval{ Start + 0.00001, Bigger };
        Root = interval.IntervalMethod(F);
        if (!std::isnan(Root)) Roots.push_back(Root);
    }

    return Roots;
}

Interval Interval::FindJ(std::vector<double> (*ptr)(double))
{
    auto F = ptr;
 
    std::vector<double> smaller = F(Smaller);
    std::vector<double> bigger = F(Bigger);

    std::vector<Interval> intervals;
    for (size_t i = 0; i < smaller.size(); ++i)
    {
        intervals.push_back({ smaller[i], bigger[i] });
    }

    Interval result = intervals[0];
    for (size_t i = 1; i < intervals.size(); ++i)
    {
        result = result * intervals[i];
    }

    return result;
}

Interval& Interval::operator=(const Interval& interval)
{
    Smaller = interval.Smaller;
    Bigger = interval.Bigger;
    return *this;
}

Interval Interval::operator*(const Interval& interval)
{
	double a = Smaller * interval.Smaller;
	double b = Smaller * interval.Bigger;
	double c = Bigger * interval.Smaller;
	double d = Bigger * interval.Bigger;

	return { std::min({a, b, c, d}), std::max({a, b, c, d}) };
}

Interval Interval::operator/(const Interval& interval)
{
    double a = Smaller / interval.Smaller;
    double b = Smaller / interval.Bigger;
    double c = Bigger / interval.Smaller;
    double d = Bigger / interval.Bigger;

    return { std::min({a, b, c, d}), std::max({a, b, c, d}) };
}

Interval Interval::operator+(const Interval& interval)
{
	return { Smaller + interval.Smaller, Bigger + interval.Bigger };
}

Interval Interval::operator-(const Interval& interval)
{
	return { Smaller - interval.Bigger, Bigger - interval.Smaller };
}
