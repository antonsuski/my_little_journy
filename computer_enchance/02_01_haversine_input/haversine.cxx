#include "haversine.hxx"

#include <cmath>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <random>

namespace random_device
{
static std::random_device rd;
static std::mt19937       generator(rd());

static std::uniform_real_distribution<> radius_gen(0, 180);
} // namespace random_device

static double square(double a)
{
    double result = a * a;
    return result;
}

static double radians_from_degrees(double degrees)
{
    double result = 0.01745329251994329577 * degrees;
    return result;
}

static haversine::pair generate_pair(const haversine::point& x_range,
                                     const haversine::point& y_range)
{
    static std::uniform_real_distribution<> xdist(x_range.x, x_range.y);
    static std::uniform_real_distribution<> ydist(y_range.x, y_range.y);

    return haversine::pair{
        { xdist(random_device::generator), ydist(random_device::generator) },
        { xdist(random_device::generator), ydist(random_device::generator) }
    };
}

namespace haversine
{
#ifndef EARTH_RADIUS
#define EARTH_RADIUS 6372.8
#endif

point generate_point(const point& center, const double& radius)
{
    static std::uniform_real_distribution<> xdist((center.x - radius),
                                                  (center.x + radius));
    static std::uniform_real_distribution<> ydist((center.y - radius),
                                                  (center.y + radius));

    point rezult{ xdist(random_device::generator),
                  ydist(random_device::generator) };

    return rezult;
}

std::vector<pair> generate_clusters(const unsigned int& pairs_count)
{
    static const int               clusters_factor{ 64 };
    std::vector<haversine::circle> clusters;

    double pairs_per_cluster{ pairs_count /
                              static_cast<double>(clusters_factor) };
    size_t pairs_in_last_cluster{ pairs_count % clusters_factor };

    double counter{ 64 };

    haversine::point points_buffer{};
    float            radius{};

    std::vector<pair> buffer;
    int               integer = pairs_per_cluster;
    double            modulo{};

    double pairs_counters = clusters_factor *

                            for (size_t i = 0; i < counter; i++){
                                // need to add cluster feeling
                            }
    {
        radius        = random_device::radius_gen(random_device::generator);
        points_buffer = generate_point({ 1, 1 }, 180);
        clusters.push_back({ points_buffer, radius });
    }

    for (auto&& i : clusters)
    {
        std::cout << i << std::endl;
    }

    std::cout << "Cluster count: " << clusters.size() << std::endl;

    generate_points_per_cluster(clusters, pairs_per_cluster);

    return std::vector<pair>{};
}

std::vector<pair> generate_points_per_cluster(
    const std::vector<circle>& clusters, const double& points_per_cluster)
{
    std::vector<pair> buffer;
    int               integer = points_per_cluster;
    double            modulo{};

    for (auto&& cluster : clusters)
    {
        modulo += points_per_cluster - integer;

        std::cout << points_per_cluster << " " << integer << " " << modulo
                  << std::endl;

        // do
        // {

        // } while (/* condition */);
    }
    return buffer;
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

std::ostream& operator<<(std::ostream& out, const circle& rhs)
{
    return out << rhs.center << " " << rhs.radius;
}

std::istream& operator>>(std::istream& in, circle& rhs)
{
    in >> rhs.center;
    in >> rhs.radius;
    return in;
}

std::ostream& operator<<(std::ostream& out, const pair& rhs)
{
    return out << rhs.first << "\n" << rhs.second;
}

std::istream& operator>>(std::istream& in, pair& rhs)
{
    in >> rhs.first;
    in >> rhs.second;

    return in;
}

double generate(nlohmann::json& buffer, const unsigned int& count,
                const std::string_view& path)
{
    using namespace nlohmann;

    const int pricise(50);
    double    sum{ 0 };
    double    kekw = count;
    double    sum_coef{ 1.0 / kekw };

    json object_buffer;
    json array_buffer;

    pair tmp_pair;

    for (size_t i = 0; i < count; i++)
    {
        tmp_pair = generate_pair({ -180.f, 180.f }, { -90.f, 90.f });

        double haversine_dist = reference_haversine(
            tmp_pair.first.x, tmp_pair.first.y, tmp_pair.second.x,
            tmp_pair.second.y, EARTH_RADIUS);

        sum += sum_coef * haversine_dist;

        object_buffer["x0"] = tmp_pair.first.x;
        object_buffer["y0"] = tmp_pair.first.y;
        object_buffer["x1"] = tmp_pair.second.x;
        object_buffer["y1"] = tmp_pair.second.y;

        array_buffer.push_back(object_buffer);
    }

    buffer["pairs"] = array_buffer;

    return sum;
}

double generate_with_cluster(nlohmann::json& buffer, const unsigned int& count,
                             const std::string_view& path)
{
    using namespace nlohmann;

    const int pricise(50);
    double    sum{ 0 };
    double    kekw = count;
    double    sum_coef{ 1.0 / kekw };

    json object_buffer;
    json array_buffer;

    pair tmp_pair;

    for (size_t i = 0; i < count; i++)
    {
        tmp_pair = generate_pair({ -180.f, 180.f }, { -90.f, 90.f });

        double haversine_dist = reference_haversine(
            tmp_pair.first.x, tmp_pair.first.y, tmp_pair.second.x,
            tmp_pair.second.y, EARTH_RADIUS);

        sum += sum_coef * haversine_dist;

        object_buffer["x0"] = tmp_pair.first.x;
        object_buffer["y0"] = tmp_pair.first.y;
        object_buffer["x1"] = tmp_pair.second.x;
        object_buffer["y1"] = tmp_pair.second.y;

        array_buffer.push_back(object_buffer);
    }

    buffer["pairs"] = array_buffer;

    return sum;
}

// NOTE(casey): EarthRadius is generally expected to be 6372.8
double reference_haversine(double X0, double Y0, double X1, double Y1,
                           double EarthRadius)
{
    /* NOTE(casey): This is not meant to be a "good" way to calculate the
       Haversine distance. Instead, it attempts to follow, as closely as
       possible, the formula used in the real-world question on which these
       homework exercises are loosely based.
    */

    double lat1 = Y0;
    double lat2 = Y1;
    double lon1 = X0;
    double lon2 = X1;

    double dLat = radians_from_degrees(lat2 - lat1);
    double dLon = radians_from_degrees(lon2 - lon1);
    lat1        = radians_from_degrees(lat1);
    lat2        = radians_from_degrees(lat2);

    double a =
        square(sin(dLat / 2.0)) + cos(lat1) * cos(lat2) * square(sin(dLon / 2));
    double c = 2.0 * asin(sqrt(a));

    double Result = EarthRadius * c;

    return Result;
}

} // namespace haversine