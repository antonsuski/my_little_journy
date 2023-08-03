#include "haversine.hxx"

#include "json.hpp"
#include "json_fwd.hpp"

#include <cassert>
#include <cstring>
#include <fstream>
#include <iomanip>
#include <iostream>

int main(int argc, char* argv[])
{
    std::cout << "Hello, haversine generator!\n";

    unsigned int count{ 10 };
    double       havers_sum{ 0 };
    std::string  path{ "test.json" };

    // Parse arguments
    // for (size_t i = 0; i < argc; i++)
    // {
    //     if (std::strcmp(argv[i], "-c") == 0)
    //     {
    //         count = std::stoi(argv[++i]);
    //     }
    //     else if (std::strcmp(argv[i], "-o") == 0)
    //     {
    //         path = argv[++i];
    //     }
    //     else if (std::strcmp(argv[i], "--cluster") == 0)
    //     {
    // std::cout << haversine::generate_point({ 100, 100 }, 10)
    //           << std::endl;
    std::cout << haversine::generate_clusters(10).size() << std::endl;
    return 0;
    //     }
    // }

    // Haversine pairs generator
    nlohmann::json buffer;
    havers_sum = haversine::generate(buffer, count, path);

    // Output pairs to file
    std::ofstream file{ path, std::ios::trunc };
    file << buffer;
    file.close();

    // Output info
    std::cout << "Method: with out cluster\n";
    std::cout << "Random seed: no seed\n";
    std::cout << "Pair count: " << count << "\n";
    std::cout << "Expected sum: " << std::setprecision(20) << havers_sum
              << "\n";

    return 0;
}
