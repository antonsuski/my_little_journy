#include "xo.hxx"

#include <algorithm>
#include <iostream>
#include <map>
#include <string>
#include <vector>

static std::map<command, std::string> command_map{ { command::set, "set" },
                                                   { command::start, "start" },
                                                   { command::end, "end" } };

static std::map<element, std::string> element_map{
    { element::cross, "x" },
    { element::zerro, "o" },
};

void print_element(const element& e)
{
    switch (e)
    {
        case element::cross:
            std::cout << "x";
            break;
        case element::zerro:
            std::cout << "o";
            break;
        case element::none:
            std::cout << "_";
            break;
    }
}

std::ostream& operator<<(std::ostream& out, const element& e)
{
    switch (e)
    {
        case element::cross:
            out << "x";
            break;
        case element::zerro:
            out << "o";
            break;
        case element::none:
            out << "_";
            break;
    }
    return out;
}

std::istream& operator>>(std::istream& in, element& e)
{
    return in;
}

std::istream& operator>>(std::istream& in, command& c)
{
    std::string buffer;
    in >> buffer;

    auto result =
        std::find_if(command_map.begin(), command_map.end(),
                     [&buffer](const auto& it) { return it.second == buffer; });
    if (result == command_map.end())
    {
        c = command::unknown;
        return in;
    }

    c = result->first;
    return in;
}

field::~field()
{
    std::cout << "Bye from, <field> destructor!" << std::endl;
}

field::field()
{
    std::cout << "Hello from, <field> default constractor!" << std::endl;

    set_element_to_all(element::none);
}

bool field::set_element(const element& e, const unsigned int& x_cord,
                        const unsigned int& y_cord)
{
    if (x_cord > 3 || y_cord > 3)
    {
        return false;
    }

    field_data[y_cord][x_cord] = e;

    return true;
}

void field::set_element_to_all(const element& e)
{
    for (auto& i : field_data)
    {
        for (auto& j : i)
        {
            j = e;
        }
    }
}

const std::array<std::array<element, 3>, 3>& field::get_field()
{
    return field_data;
}

void view::render_field(field& f)
{
    for (const auto i : f.get_field())
    {
        for (const auto j : i)
        {
            std::cout << j << "|";
        }
        std::cout << std::endl;
    }
}

void game::run()
{
    bool    running{ true };
    command c{ command::unknown };

    // clang-format off
    std::cout << "Welcome to tic-tak-toe Version 1.0" << std::endl;
    std::cout << "For start type \"start\"\nFor set x or o type \"set\"\nFor "
                 "end game type \"end\"\n"
              << "Good luck, and have fun!" << std::endl;
    // clang-format on

    while (running)
    {
        std::cout << ">";
        std::cin >> c;

        switch (c)
        {
            case command::start:
            {
                std::cout << "start\n";
            }
            break;
            case command::end:
            {
                std::cout << "end\n";
                running = false;
            }
            break;
            case command::set:
            {
                uint16_t pos_x, pos_y;
                element  e{ element::none };

                std::cout << "set\n";
                std::cout << "Enter position x: >";
                std::cin >> pos_x;
                std::cout << "Enter position y: >";
                std::cin >> pos_y;
                std::cout << "Enter x or o: >";
                std::cin >> e;

                game_board.set_element(e, pos_x, pos_y);
            }
            break;
        }
    }
}
