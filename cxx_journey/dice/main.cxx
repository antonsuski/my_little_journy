#include <chrono>
#include <iostream>
#include <limits>
#include <map>
#include <random>
#include <string>
#include <string_view>
#include <vector>

namespace handle
{
namespace options
{
struct option
{
    enum type
    {
        limit,
        statistics,
        none
    };

    // std::string value;
    type kind;
};

std::vector<option::type> args{};

bool parse(int argc, char** argv)
{
    if (argc > 2)
    {
        std::cout << "Too many argumets\n"
                  << "Usage: dice\n"
                  << "Usage: dice -l [min_limit] [max_limit]" << std::endl;
    }
    const std::vector<std::string_view> buffer(argv + 1, argv + argc);

    if (buffer.empty())
    {
        return false;
    }

    for (const auto& arg : buffer)
    {
        if (arg == "-l" || arg == "-limit")
        {
            args.push_back({ option::type::limit });
        }
    }

    return true;
}

} // namespace options

void ignore_line(void)
{
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void cin_extraction(void)
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
} // namespace handle

namespace prng
{
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
    handle::cin_extraction();
    return res;
}
} // namespace prng

using ui = unsigned int;
using i  = int;

int main(int argc, char** argv)
{
    int min = { 0 };
    int max = { 6 };

    std::cout << prng::get_range(min, max) << std::endl;
    return 0;
}
