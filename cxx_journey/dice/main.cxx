#include <algorithm>
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
std::vector<std::string_view> args{};

bool parse(int argc, char** argv)
{
    // [explicit_first_arg]
    // --limit [min] [max]
    // --statistis
    // --recursive [number]
    if (argc > 8)
    {
        std::cout << "Too many argumets\n"
                  << "Usage: dice\n"
                  << "Usage: dice -l [min] [max]" << std::endl;
    }

    const std::vector<std::string_view> buffer(argv + 1, argv + argc);

    if (buffer.empty())
    {
        return false;
    }

    args = buffer;
    return true;
}

std::vector<std::string_view> get_option(const std::string_view& option_name)
{
    auto it = std::find_if(args.begin(), args.end(),
                           [&option_name](std::string_view arg) {
                               return option_name == arg ||
                                      option_name.substr(1, 2) == arg;
                           });
    if (it != args.end())
    {
        std::vector<std::string_view> buffer{};
        if (*it == "-l" || *it == "--limit")
        {
            for (size_t i{ 0 }; i < 3; i++)
            {
                buffer.push_back(*it);
                if ((++it) == args.end())
                {
                    std::cout << "Wrong usage."
                              << "Usage: dice -l [min] [max]\n"
                              << "Usage: dice --lilmit [min] [max]"
                              << std::endl;
                }
            }
        }
        if (*it == "-r" || *it == "--recursive")
        {
            for (size_t i{ 0 }; i < 2; i++)
            {
                if ((++it) == args.end())
                {
                    std::cout << "Wrong usage."
                              << "Usage: dice -r [number]\n"
                              << "Usage: dice --recursive [number]"
                              << std::endl;
                }
            }
        }
        if (*it == "-h" || *it == "--help")
        {
            buffer.push_back(*it);
        }
        if (*it == "-s" || *it == "--statistics")
        {
            buffer.push_back(*it);
        }
        return buffer;
    }

    return { { "none" } };
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
    if (handle::options::parse(argc, argv))
    {
        std::cout << "There are some argumets\n";

        for (auto arg : handle::options::args)
        {
            std::cout << arg << std::endl;
        }
    }
    std::cout << prng::get_range(min, max) << std::endl;
    return 0;
}
