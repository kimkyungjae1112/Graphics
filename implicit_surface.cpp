#include "implicit_surface.h"
#include "interval.h"
#include <cmath>
#include <limits>
#include <optional>
#include <iostream>

ImplicitSurface::ImplicitSurface(const std::vector<Vector>& metaballs, double isoValue, const Color& color)
    : metaballs(metaballs), isoValue(isoValue), color(color)
{
}

bool ImplicitSurface::Intersect(const Vector& origin, const Vector& direction, double& tt) const
{
    const auto& func_im = [&](const auto& t)
        {
            const Vector oc = origin - metaballs[0];
            const double a = direction.DotProduct(direction);
            const double b = direction.DotProduct(oc);
            const double c = oc.DotProduct(oc);
            auto ret = exp(-(a * t * t + 2 * b * t + c));
            for (size_t i = 1; i < metaballs.size(); i++)
            {
                const Vector oc = origin - metaballs[i];
                const double b = direction.DotProduct(oc);
                const double c = oc.DotProduct(oc);
                ret = ret + exp(-(a * t * t + 2 * b * t + c));
            }

            return ret - isoValue;
        };

    std::optional<double> root = IntervalMethod(func_im, {-100, 100});
    if (root.has_value())
    {
        tt = root.value();
        return true;
    }
    return false;
}

Vector ImplicitSurface::GetNormal(const Vector& point) const
{
    //법선벡터를 구하기 위한 함수
    const auto& func_normal = [&](const Vector& p)
        {
            double ret = 0;
            for (size_t i = 0; i < metaballs.size(); i++)
            {
                const Vector& pc = p - metaballs[i];
                ret += exp(-pc.DotProduct(pc));
            }
            return ret;
        };

    constexpr double delta = 1e-5;
    Vector normal = Vector(
        func_normal({ point.x + delta, point.y, point.z }) - func_normal({ point.x - delta, point.y, point.z }),
        func_normal({ point.x, point.y + delta, point.z }) - func_normal({ point.x, point.y - delta, point.z }),
        func_normal({ point.x, point.y, point.z + delta }) - func_normal({ point.x, point.y, point.z - delta })
    ).Normalization();

    return normal;
}

Color ImplicitSurface::GetColor() const
{
    return color;
}
