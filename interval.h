#pragma once
#ifndef __INTERVAL_H__
#define __INTERVAL_H__
#include <vector>

class Interval
{
public:
	Interval() {};
	Interval(const double& a, const double& b) : Smaller(a), Bigger(b) {}

	double IntervalMethod(std::vector<double>(*ptr)(double));
	std::vector<double> FindAllRoot(std::vector<double>(*F)(double));

	Interval& operator=(const Interval& interval);
	Interval operator*(const Interval& interval);
	Interval operator/(const Interval& interval);
	Interval operator+(const Interval& interval);
	Interval operator-(const Interval& interval);
	

private:
	Interval FindJ(std::vector<double> (*ptr)(double));

	double Smaller;
	double Bigger;
};

#endif // !__INTERVAL_H__
