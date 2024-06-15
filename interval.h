#pragma once
#ifndef __INTERVAL_H__
#define __INTERVAL_H__
#include <functional>
#include <optional>
#include <numeric>
#include <ostream>

class Interval
{
public:
    double Smaller;
    double Bigger;

    Interval(const double& smaller, const double& bigger)
        : Smaller(smaller), Bigger(bigger)
    {
    }

    Interval operator*(const Interval& interval) const;
    Interval operator/(const Interval& interval) const;
    Interval operator+(const Interval& interval) const;
    Interval operator-(const Interval& interval) const;
    
    Interval operator+(const double& i) const;
    Interval operator-(const double& i) const;
    Interval operator*(const double& i) const;
    Interval operator-() const;

    friend Interval operator+(const double& i, const Interval& interval);
    friend Interval operator-(const double& i, const Interval& interval);
    friend Interval operator*(const double& i, const Interval& interval);
    
    
    friend Interval exp(const Interval& interval);
    friend std::ostream& operator<<(std::ostream& os, const Interval& interval);


    double Range() const
    {
        return Bigger - Smaller;
    }
    double Center() const
    {
        return (Bigger + Smaller) / 2;
    }
    bool Contain(const double& i) const
    { 
        return Bigger >= i && Smaller <= i;
    }

    
};

std::ostream& operator<<(std::ostream& os, const Interval& interval);
std::optional<double> IntervalMethod(const std::function<Interval(Interval)>& func, const Interval& i);

#endif //__INTERVAL_H__