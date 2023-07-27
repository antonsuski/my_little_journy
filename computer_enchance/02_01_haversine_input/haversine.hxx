#pragma once

#include <iostream>

namespace haversine
{
struct point
{
    long double x{};
    long double y{};

    friend std::ostream& operator<<(std::ostream& out, const point& rhs);
    friend std::istream& operator>>(std::istream& in, point& rhs);
};

point generate_point(const point& x_range, const point& y_range);

void generate(const float& earth_radius);
} // namespace haversine
