#include "haversine.hxx"

#include "json.hpp"
#include "json_fwd.hpp"

#include <ctime>
#include <iomanip>
#include <iostream>
#include <random>

namespace haversine
{
point generate_point(const point& x_range, const point& y_range)
{
    static std::random_device rd;
    static std::mt19937       generator(rd());

    std::uniform_real_distribution<> xdist(x_range.x, x_range.y);
    std::uniform_real_distribution<> ydist(y_range.x, y_range.y);

    return point{ xdist(generator), ydist(generator) };
}

std::ostream& operator<<(std::ostream& out, const point& rhs)
{
    return out << rhs.x << " " << rhs.y;
}
std::istream& operator>>(std::istream& in, point& rhs)
{
    in >> rhs.x;
    in >> rhs.y;
    return in;
}

void generate(const float& earth_radius)
{
    using namespace nlohmann;

    json buffer;
    json object_buffer;
    json array_buffer;

    const int size = { 10 };
    const int pricise(50);

    for (size_t i = 0; i < size; i++)
    {
        point tmp_first_point =
            generate_point({ -180.f, 180.f }, { -90.f, 90.f });
        object_buffer["x0"] = tmp_first_point.x;
        object_buffer["y0"] = tmp_first_point.y;

        point tmp_second_point =
            generate_point({ -180.f, 180.f }, { -90.f, 90.f });
        object_buffer["x1"] = tmp_first_point.x;
        object_buffer["y1"] = tmp_first_point.y;

        array_buffer.push_back(object_buffer);

        std::cout << std::setw(10) << std::right << "first: " << std::fixed
                  << std::setw(pricise + 5) << std::right
                  << std::setprecision(pricise) << tmp_first_point << std::endl;
        std::cout << std::setw(10) << std::right << "second: " << std::fixed
                  << std::setw(pricise + 5) << std::right
                  << std::setprecision(pricise) << tmp_second_point
                  << std::endl;
    }

    buffer["pairs"] = array_buffer;

    std::cout << buffer;
}
} // namespace haversine
