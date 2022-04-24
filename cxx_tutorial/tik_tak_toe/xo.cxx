#include "xo.hxx"

#include <algorithm>
#include <iostream>
#include <map>
#include <string>
#include <vector>

static std::map<command, std::string> command_map{ { command::set_element,
                                                     "set" },
                                                   { command::start, "start" },
                                                   { command::end, "end" } };

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

    for (auto& i : field_data)
    {
        for (auto& j : i)
        {
            j = element::none;
        }
    }
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
