#pragma once

#include "json.hpp"
#include "json_fwd.hpp"

#include <iostream>
#include <string_view>

namespace haversine
{

struct point
{
    long double x{};
    long double y{};

    friend std::ostream& operator<<(std::ostream& out, const point& rhs);
    friend std::istream& operator>>(std::istream& in, point& rhs);
};

struct pair
{
    point first{};
    point second;

    friend std::ostream& operator<<(std::ostream& out, const pair& rhs);
    friend std::istream& operator>>(std::istream& in, pair& rhs);
};

pair generate_point(const point& x_range, const point& y_range);

double generate(nlohmann::json& buffer, const unsigned int& count,
                const std::string_view& path);

static double reference_haversine(double X0, double Y0, double X1, double Y1,
                                  double EarthRadius);
} // namespace haversine
