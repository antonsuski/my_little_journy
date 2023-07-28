#include "haversine.hxx"

#include "json.hpp"
#include "json_fwd.hpp"

#include <cassert>
#include <cstring>
#include <fstream>
#include <iostream>

int main(int argc, char* argv[])
{
    std::cout << "Hello, haversine generator!\n";

    unsigned int count{ 10 };
    std::string  path{ "test.json" };
    std::string  format{ "json" };

    for (size_t i = 0; i < argc; i++)
    {
        std::cout << argv[i] << std::endl;

        if (std::strcmp(argv[i], "-c") == 0)
        {
            count = std::stoi(argv[++i]);
            std::cout << "count:" << count << "\n";
        }
        else if (std::strcmp(argv[i], "-o") == 0)
        {
            path = argv[++i];
            std::cout << "path:" << path + "\n";
        }

        // else if (argv[i] == "-f")
        // {
        //     format = argv[++i];
        //     std::cout << "count:" << format + "\n";
        // }
    }

    // Haversine pairs generator
    nlohmann::json buffer;
    haversine::generate(buffer, count, path);

    // Output pairs to file
    std::ofstream file{ path, std::ios::trunc };
    file << buffer;
    file.close();

    return 0;
}
