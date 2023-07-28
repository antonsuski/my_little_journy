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

point generate_point(const point& x_range, const point& y_range);

void generate(nlohmann::json& buffer, const unsigned int& count,
              const std::string_view& path);

} // namespace haversine
