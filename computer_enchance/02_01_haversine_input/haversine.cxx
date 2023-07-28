#include "haversine.hxx"

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

    static std::uniform_real_distribution<> xdist(x_range.x, x_range.y);
    static std::uniform_real_distribution<> ydist(y_range.x, y_range.y);

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

void generate(nlohmann::json& buffer, const unsigned int& count,
              const std::string_view& path)
{
    using namespace nlohmann;

    json object_buffer;
    json array_buffer;

    const int pricise(50);

    point tmp_first_point;
    point tmp_second_point;

    for (size_t i = 0; i < count; i++)
    {
        tmp_first_point = generate_point({ -180.f, 180.f }, { -90.f, 90.f });
        object_buffer["x0"] = tmp_first_point.x;
        object_buffer["y0"] = tmp_first_point.y;

        tmp_second_point = generate_point({ -180.f, 180.f }, { -90.f, 90.f });
        object_buffer["x1"] = tmp_first_point.x;
        object_buffer["y1"] = tmp_first_point.y;

        array_buffer.push_back(object_buffer);

        // std::cout << std::setw(10) << std::right << "first: " << std::fixed
        //           << std::setw(pricise + 5) << std::right
        //           << std::setprecision(pricise) << tmp_first_point << "\n";
        // std::cout << std::setw(10) << std::right << "second: " << std::fixed
        //           << std::setw(pricise + 5) << std::right
        //           << std::setprecision(pricise) << tmp_second_point << "\n";
    }

    buffer["pairs"] = array_buffer;
}
} // namespace haversine
