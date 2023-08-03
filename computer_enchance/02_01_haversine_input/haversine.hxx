#pragma once

#include "json.hpp"
#include "json_fwd.hpp"

#include <iostream>
#include <string_view>

namespace haversine
{

struct point
{
    double x{};
    double y{};

    friend std::ostream& operator<<(std::ostream& out, const point& rhs);
    friend std::istream& operator>>(std::istream& in, point& rhs);
};

struct circle
{
    point center{};
    float radius{};

    friend std::ostream& operator<<(std::ostream& out, const circle& rhs);
    friend std::istream& operator>>(std::istream& in, circle& rhs);
};

struct pair
{
    point first{};
    point second;

    friend std::ostream& operator<<(std::ostream& out, const pair& rhs);
    friend std::istream& operator>>(std::istream& in, pair& rhs);
};

double generate(nlohmann::json& buffer, const unsigned int& count,
                const std::string_view& path);

double generate_with_cluster(nlohmann::json& buffer, const unsigned int& count,
                             const std::string_view& path);

double reference_haversine(double X0, double Y0, double X1, double Y1,
                           double EarthRadius);

point             generate_point(const point& center, const double& radius);
std::vector<pair> generate_clusters(const unsigned int& pairs_count);
std::vector<pair> generate_points_per_cluster(
    const std::vector<circle>& clusters, const double& points_per_cluster);
} // namespace haversine
