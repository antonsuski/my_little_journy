#include <chrono>
#include <iostream>
#include <limits>
#include <random>

namespace prng
{
namespace
{
void ignore_line(void)
{
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void handle_cin_stream(void)
{
    if (!std::cin)
    {
        if (std::cin.eof())
        {
            std::exit(0);
        }
        std::cin.clear();
    }

    ignore_line();
}
} // namespace

inline std::mt19937 init_prng(void)
{
    std::random_device rd{};
    std::seed_seq      ss{
        rd(),
        static_cast<std::seed_seq::result_type>(
            std::chrono::steady_clock::now().time_since_epoch().count()),
        rd()
    };
    return std::mt19937{ ss };
}

inline std::mt19937 mt{ init_prng() };

inline int get_range(int min, int max)
{
    return std::uniform_int_distribution{ min, max }(mt);
}

inline int get_input()
{
    int res{ 0 };
    std::cin >> res;
    handle_cin_stream();
    return res;
}
} // namespace prng

using ui = unsigned int;
using i  = int;

int main(int argc, char** argv)
{
    std::cout << prng::get_range(0u, 6u) << std::endl;
    return 0;
}
